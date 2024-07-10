/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file writing_files_with_2_thread.c
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
#include <errno.h>  // Added for perror

FILE *fp;
pthread_mutex_t file_mutex;

/**
 * @brief Thread function to write numbers to a file.
 * 
 * @param arg Pointer to an integer indicating thread's role (0 or 1).
 * @return void* Always returns NULL.
 */

void *WriteNumbers(void *arg)
{
    int *temp = (int *)arg;
    if (*temp == 0)
    {
        for (int i = 1; i <= 1000; i++)
        {
            if (pthread_mutex_lock(&file_mutex) != 0)  // Check return value for pthread_mutex_lock
            {
                perror("pthread_mutex_lock");
                return NULL;
            }
            fprintf(fp, "%c\t%d\n", '#', i);
            if (pthread_mutex_unlock(&file_mutex) != 0)  // Check return value for pthread_mutex_unlock
            {
                perror("pthread_mutex_unlock");
                return NULL;
            }
        }
    }
    else
    {
        for (int i = 1; i <= 1000; i++)
        {
            if (pthread_mutex_lock(&file_mutex) != 0)  // Check return value for pthread_mutex_lock
            {
                perror("pthread_mutex_lock");
                return NULL;
            }
            fprintf(fp, "%c\t%d\n", '$', i);
            if (pthread_mutex_unlock(&file_mutex) != 0)  // Check return value for pthread_mutex_unlock
            {
                perror("pthread_mutex_unlock");
                return NULL;
            }
        }
    }
    free(arg);
    return NULL;
}

/**
 * @brief Main function where threads are created and joined.
 * 
 * @return int Returns EXIT_SUCCESS upon successful completion, EXIT_FAILURE otherwise.
 */

int main()
{
    pthread_t threads[2];
    pthread_mutex_init(&file_mutex, NULL);

    fp = fopen("./files/numbers.txt", "w");
    if (fp == NULL)
    {
        fp = fopen("../files/numbers.txt", "w");
        if (fp == NULL)
        {
            perror("Unable to open file");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        int *temp = malloc(sizeof(int));
        if (temp == NULL)  // Check if malloc succeeds
        {
            perror("malloc");
            return EXIT_FAILURE;
        }
        *temp = i;
        if (pthread_create(&threads[i], NULL, WriteNumbers, temp) != 0)  // Check return value for pthread_create
        {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)  // Check return value for pthread_join
        {
            perror("pthread_join");
            return EXIT_FAILURE;
        }
    }

    if (fclose(fp) != 0)  // Check return value for fclose
    {
        perror("fclose");
        return EXIT_FAILURE;
    }

    if (pthread_mutex_destroy(&file_mutex) != 0)  // Check return value for pthread_mutex_destroy
    {
        perror("pthread_mutex_destroy");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

