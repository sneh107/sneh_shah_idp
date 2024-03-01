#include <stdio.h>
 
int main()
{

    int arr[5] = { 10, 20, 30, 40, 50 };

    int arr1[] = { 1, 2, 3, 4, 5 };
 
    float arr2[5];
    for (int i = 0; i < 5; i++) {
        arr2[i] = i * 2.1;
    }

    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Elements or size of array: %d\n",size);

    printf("For arr\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", arr[i]);
    }

    printf("For arr1\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", arr1[i]);
    }

    printf("For arr2\n");
    for (int i = 0; i < 5; i++) {
        printf("%f\n", arr2[i]);
    }
    return 0;
}