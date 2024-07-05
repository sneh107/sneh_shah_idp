#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define bufferSize 10
#define readSize 1024

typedef struct bufferr
{
    char buff[readSize];
    size_t size;
} buffer_t;

typedef struct stats
{
    float readCompletion;
    int iterationCount;
    int numWordsRead;
} stats_t;

buffer_t buffer[bufferSize];
int count = 0;
int producerFinished = 0;
int terminate = 0;
pthread_mutex_t mutex;
pthread_cond_t condNotEmpty, condNotFull, condStats;
FILE *input = NULL;
FILE *output = NULL;
stats_t producerStats = {0};
stats_t consumerStats[2] = {0};
long totalSize = 0;
pthread_t bookKeepingThread;

void calculateStats(stats_t *stats, char *buffer, size_t size)
{
    stats->numWordsRead = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] == ' ' || buffer[i] == '\n')
            stats->numWordsRead++;
    }
    stats->iterationCount++;
    stats->readCompletion = (ftell(input) * 100.0) / totalSize;
}

void encrypt_data(char *data, size_t size, int offset)
{
    for (size_t i = 0; i < size; i++)
    {
        data[i] += offset;
    }
}

void *producer(void *arg)
{
    printf("Producer thread started\n");
    while (1)
    {
        sleep(1); // producing

        pthread_mutex_lock(&mutex);

        while (count == bufferSize)
        {
            printf("Buffer full. Producer is waiting.\n");
            pthread_cond_wait(&condNotFull, &mutex);
        }

        if (feof(input) || terminate)
        {
            producerFinished = 1;
            printf("Producer finished reading the file.\n");
            pthread_cond_broadcast(&condNotEmpty);
            pthread_cond_signal(&condStats);
            pthread_mutex_unlock(&mutex);
            break;
        }

        size_t readBytes = fread(buffer[count].buff, 1, readSize, input);
        if (readBytes > 0)
        {
            buffer[count].size = readBytes;
            printf("Producer read %zu bytes and added to buffer. Buffer count: %d\n", readBytes, count + 1);
            calculateStats(&producerStats, buffer[count].buff, readBytes);
            count++;
            pthread_cond_signal(&condNotEmpty);
        }

        pthread_cond_signal(&condStats);
        pthread_mutex_unlock(&mutex);
    }
    printf("Producer thread exiting\n");
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int interval = *(int *)arg;
    int consumerIndex = interval - 2;
    int encryptionOffset = (interval == 2) ? 0x50 : 0x60;
    printf("Consumer thread with interval %d started\n", interval);

    while (1)
    {
        sleep(interval); // consuming

        pthread_mutex_lock(&mutex);

        while (count == 0 && !producerFinished)
        {
            printf("Buffer empty. Consumer with interval %d is waiting.\n", interval);
            pthread_cond_wait(&condNotEmpty, &mutex);
        }

        if (count == 0 && producerFinished)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        buffer_t toWrite = buffer[0];
        for (int i = 1; i < count; i++)
        {
            buffer[i - 1] = buffer[i];
        }
        count--;

        // encrypt_data(toWrite.buff, toWrite.size, encryptionOffset);
        fwrite(toWrite.buff, 1, toWrite.size, output);
        printf("Consumer with interval %d processed a chunk of %zu bytes. Buffer count: %d\n", interval, toWrite.size, count);
        calculateStats(&consumerStats[consumerIndex], toWrite.buff, toWrite.size);

        pthread_cond_signal(&condNotFull);
        pthread_cond_signal(&condStats);
        pthread_mutex_unlock(&mutex);
    }
    printf("Consumer thread with interval %d exiting\n", interval);
    pthread_exit(NULL);
}

void *bookKeeper(void *arg)
{
    printf("Book-keeping thread started\n");
    while (1)
    {
        pthread_mutex_lock(&mutex);

        pthread_cond_wait(&condStats, &mutex);
        if (terminate && producerFinished && count == 0)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("=== Statistics ===\n");
        printf("Producer: %0.2f%% complete, Iterations: %d, Words Read: %d\n",
               producerStats.readCompletion, producerStats.iterationCount, producerStats.numWordsRead);
        for (int i = 0; i < 2; i++)
        {
            printf("Consumer %d: Iterations: %d, Words Read: %d\n",
                   i + 1, consumerStats[i].iterationCount, consumerStats[i].numWordsRead);
        }

        pthread_mutex_unlock(&mutex);
    }
    printf("Book-keeping thread exiting\n");
    pthread_exit(NULL);
}

void handle_sigint(int sig)
{
    printf("SIGINT received, terminating gracefully...\n");
    terminate = 1;
    pthread_cond_broadcast(&condNotFull);
    pthread_cond_broadcast(&condNotEmpty);
    pthread_cond_signal(&condStats);
}

int main()
{
    signal(SIGINT, handle_sigint);

    pthread_t producerThread;
    pthread_t consumerThreads[2];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condNotEmpty, NULL);
    pthread_cond_init(&condNotFull, NULL);
    pthread_cond_init(&condStats, NULL);

    input = fopen("./files/input.txt", "r");
    output = fopen("./files/output.txt", "a");
    if (input == NULL)
    {
        input = fopen("../files/input.txt", "r");
        if (input == NULL)
        {
            perror("Unable to open file");
            return -1;
        }
        // perror("Unable to open file");
        // return -1;
    }
    if (output == NULL)
    {
        output = fopen("../files/output.txt", "a");
        if (output == NULL)
        {
            perror("Unable to open file");
            return -1;
        }
        // perror("Unable to open file");
        // return -1;
    }

    fseek(input, 0, SEEK_END);
    totalSize = ftell(input);
    fseek(input, 0, SEEK_SET);

    int consumerIntervals[2] = {2, 3};

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&bookKeepingThread, NULL, bookKeeper, NULL);

    for (int index = 0; index < 2; index++)
    {
        pthread_create(&consumerThreads[index], NULL, consumer, &consumerIntervals[index]);
        usleep(100);
    }

    pthread_join(producerThread, NULL);
    for (int index = 0; index < 2; index++)
    {
        pthread_join(consumerThreads[index], NULL);
    }
    terminate = 1;
    pthread_cond_signal(&condStats);
    pthread_join(bookKeepingThread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condNotEmpty);
    pthread_cond_destroy(&condNotFull);
    pthread_cond_destroy(&condStats);
    fclose(input);
    fclose(output);

    return 0;
}