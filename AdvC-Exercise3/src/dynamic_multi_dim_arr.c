#include <stdio.h>
#include <stdlib.h>

int main()
{
    int row = 2, col = 3;
    int **arr;
    arr = (int **)malloc(row * sizeof(int *));

    for (int i = 0; i < row; i++)
    {
        arr[i] = (int *)malloc(col * sizeof(int));
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            arr[i][j] = i + j;
        }
    }

    printf("%d\n", arr[1][2]);

    for (int i = 0; i < row; i++)
    {
        free(arr[i]);
    }

    free(arr);

    return 0;
}