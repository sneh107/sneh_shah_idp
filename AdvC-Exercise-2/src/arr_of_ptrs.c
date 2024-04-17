#include <stdio.h>

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    int *arr_ptr[5];

    for (int i = 0; i < 5; i++)
    {
        arr_ptr[i] = &arr[i];
    }

    // or int* arr_ptr[5] = { &arr[1], &arr[2], &arr[3], &arr[4], &arr[5] };

    for (int i = 0; i < 5; i++)
    {
        printf("arr[%d]: %d\n", i, *arr_ptr[i]);
    }

    return 0;
}