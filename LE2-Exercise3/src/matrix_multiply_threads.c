/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file matrix_multiply_threads.c
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Jun/3/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 3

int first[SIZE][SIZE];
int second[SIZE][SIZE];
int result[SIZE][SIZE];

/**
 * @brief Structure to hold matrix element position.
 * 
 * This structure holds the row and column indices for a matrix element,
 * used to pass data to the thread function.
 */

typedef struct
{
    int row;
    int col;
} MatrixElement_t;

/**
 * @brief Thread function to perform matrix multiplication for a single element.
 * 
 * This function computes the value of a single element in the resultant matrix
 * by multiplying the corresponding row of the first matrix with the column of
 * the second matrix.
 * 
 * @param arg Pointer to the MatrixElement_t structure containing row and column indices.
 * @return void* Returns NULL on completion.
 */
 

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

/**
 * @brief Main function to perform matrix multiplication using threads.
 * 
 * The function initializes two matrices with user input, creates a thread for each element
 * in the resultant matrix to perform the multiplication, and then waits for all threads
 * to complete before printing the resultant matrix.
 * 
 * @return int Returns 0 on successful completion.
 */

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
            if (cell == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            cell->row = i;
            cell->col = j;
            if (pthread_create(&threads[i][j], NULL, MatrixMultiplication, (void *)cell)) {
                perror("Error creating thread");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (pthread_join(threads[i][j], NULL)) {
                perror("Error joining thread");
                exit(EXIT_FAILURE);
            }
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

