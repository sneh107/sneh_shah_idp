#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

FILE *fp;
pthread_mutex_t file_mutex;

void *WriteNumbers(void *arg)
{
    int *temp = (int *)arg;
    if (*temp == 0)
    {
        // pthread_mutex_lock(&file_mutex); // if i lock outside for loop it will complete counting whole 1-1000
        for (int i = 1; i <= 1000; i++)
        {
            pthread_mutex_lock(&file_mutex); // if i lock inside for loop 2 nd thread can come in between and write its nos.
            fprintf(fp, "%c\t%d\n", '#', i);
            pthread_mutex_unlock(&file_mutex);
        }
        // pthread_mutex_unlock(&file_mutex);
    }
    else
    {
        for (int i = 1; i <= 1000; i++)
        {
            pthread_mutex_lock(&file_mutex);
            fprintf(fp, "%c\t%d\n", '$', i);
            pthread_mutex_unlock(&file_mutex);
        }
    }
    free(arg);
    return NULL;
}

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
        *temp = i;
        pthread_create(&threads[i], NULL, WriteNumbers, temp);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
    }

    fclose(fp);
    pthread_mutex_destroy(&file_mutex);

    return EXIT_SUCCESS;
}
