#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size;
    printf("Enter no. of Elements: ");
    scanf("%d", &size);

    int *arr = (int *)calloc(size, sizeof(int));

    if (arr == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }

    for (int i = 0; i < size; i++)
    {
        printf("Enter arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < size; i++)
    {
        printf("arr[%d]: %d\n", i, arr[i]);
    }

    free(arr);

    return 0;
}