#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 3

int first[SIZE][SIZE];
int second[SIZE][SIZE];
int result[SIZE][SIZE];

typedef struct
{
    int row;
    int col;
} MatrixElement_t;

void *MatrixMultiplication(void *arg)
{
    MatrixElement_t *cell = (MatrixElement_t *)arg;
    int row = cell->row;
    int col = cell->col;
    int sum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        sum += first[row][i] * second[i][col];
    }
    result[row][col] = sum;
    pthread_exit(NULL);
}

int main()
{
    printf("Enter elements for first matrix:\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("Enter element first[%d][%d]: ", i, j);
            scanf("%d", &first[i][j]);
        }
    }

    printf("Enter elements for second matrix:\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("Enter element second[%d][%d]: ", i, j);
            scanf("%d", &second[i][j]);
        }
    }

    pthread_t threads[SIZE][SIZE];
    int i, j;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            MatrixElement_t *cell = (MatrixElement_t *)malloc(sizeof(MatrixElement_t));
            cell->row = i;
            cell->col = j;
            pthread_create(&threads[i][j], NULL, MatrixMultiplication, (void *)cell);
        }
    }

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            pthread_join(threads[i][j], NULL);
        }
    }

    printf("Resultant Matrix:\n");
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}