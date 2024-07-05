#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define bufferSize 10
#define readSize 1024

typedef struct bufferr
{
    char buff[readSize];
    size_t size;
} buffer_t;

buffer_t buffer[bufferSize];
int count = 0;
int producerFinished = 0;
pthread_mutex_t mutex;
pthread_cond_t condNotEmpty, condNotFull;
FILE *input = NULL;
FILE *output = NULL;

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

        if (feof(input))
        {
            producerFinished = 1;
            printf("Producer finished reading the file.\n");
            pthread_cond_broadcast(&condNotEmpty);
            pthread_mutex_unlock(&mutex);
            break;
        }

        size_t readBytes = fread(buffer[count].buff, 1, readSize, input);
        if (readBytes > 0)
        {
            buffer[count].size = readBytes;
            printf("Producer read %zu bytes and added to buffer. Buffer count: %d\n", readBytes, count + 1);
            count++;
            pthread_cond_signal(&condNotEmpty);
        }

        pthread_mutex_unlock(&mutex);
    }
    printf("Producer thread exiting\n");
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int interval = *(int *)arg;
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

        pthread_cond_signal(&condNotFull);
        pthread_mutex_unlock(&mutex);
    }
    printf("Consumer thread with interval %d exiting\n", interval);
    pthread_exit(NULL);
}

int main()
{
    pthread_t producerThread;
    pthread_t consumerThreads[2];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condNotEmpty, NULL);
    pthread_cond_init(&condNotFull, NULL);

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

    int consumerIntervals[2] = {2, 3};

    pthread_create(&producerThread, NULL, producer, NULL);

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

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condNotEmpty);
    pthread_cond_destroy(&condNotFull);
    fclose(input);
    fclose(output);

    return 0;
}
