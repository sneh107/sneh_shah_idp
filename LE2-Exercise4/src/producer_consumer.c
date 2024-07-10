/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file producer_consumer.c
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Jun/5/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define bufferSize 10
#define readSize 1024

/**
 * @brief Structure to hold buffer data.
 * 
 * This structure holds the data and its size for each buffer element.
 */

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

/**
 * @brief Function to encrypt data.
 * 
 * This function performs a simple encryption by adding an offset to each byte of the data.
 * 
 * @param data Pointer to the data to be encrypted.
 * @param size Size of the data.
 * @param offset Encryption offset.
 */

void encrypt_data(char *data, size_t size, int offset)
{
    for (size_t i = 0; i < size; i++)
    {
        data[i] += offset;
    }
}

/**
 * @brief Producer thread function.
 * 
 * This function reads chunks of data from the input file and places them into the buffer.
 * It signals the consumers when new data is available and waits if the buffer is full.
 * 
 * @param arg Pointer to the arguments for the producer (unused).
 * @return void* Returns NULL on completion.
 */

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

/**
 * @brief Consumer thread function.
 * 
 * This function consumes data from the buffer, processes it (optionally encrypting it),
 * and writes it to the output file. It waits if the buffer is empty and signals the
 * producer when it consumes data.
 * 
 * @param arg Pointer to the interval for the consumer thread.
 * @return void* Returns NULL on completion.
 */

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
        if (fwrite(toWrite.buff, 1, toWrite.size, output) != toWrite.size)
        {
            perror("Error writing to output file");
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        printf("Consumer with interval %d processed a chunk of %zu bytes. Buffer count: %d\n", interval, toWrite.size, count);

        pthread_cond_signal(&condNotFull);
        pthread_mutex_unlock(&mutex);
    }
    printf("Consumer thread with interval %d exiting\n", interval);
    pthread_exit(NULL);
}

/**
 * @brief Main function to initialize resources and create threads.
 * 
 * The function initializes mutexes and condition variables, opens the input and output files,
 * creates the producer and consumer threads, and waits for their completion.
 * 
 * @return int Returns 0 on successful completion, or -1 if an error occurs.
 */

int main()
{
    pthread_t producerThread;
    pthread_t consumerThreads[2];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condNotEmpty, NULL);
    pthread_cond_init(&condNotFull, NULL);

    input = fopen("./files/input.txt", "r");
    if (input == NULL)
    {
        input = fopen("../files/input.txt", "r");
        if (input == NULL)
        {
            perror("Unable to open input file");
            return -1;
        }
    }

    output = fopen("./files/output.txt", "a");
    if (output == NULL)
    {
        output = fopen("../files/output.txt", "a");
        if (output == NULL)
        {
            perror("Unable to open output file");
            return -1;
        }
    }

    int consumerIntervals[2] = {2, 3};

    if (pthread_create(&producerThread, NULL, producer, NULL))
    {
        perror("Error creating producer thread");
        return -1;
    }

    for (int index = 0; index < 2; index++)
    {
        if (pthread_create(&consumerThreads[index], NULL, consumer, &consumerIntervals[index]))
        {
            perror("Error creating consumer thread");
            return -1;
        }
        usleep(100);
    }

    if (pthread_join(producerThread, NULL))
    {
        perror("Error joining producer thread");
        return -1;
    }
    for (int index = 0; index < 2; index++)
    {
        if (pthread_join(consumerThreads[index], NULL))
        {
            perror("Error joining consumer thread");
            return -1;
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condNotEmpty);
    pthread_cond_destroy(&condNotFull);
    fclose(input);
    fclose(output);

    return 0;
}

