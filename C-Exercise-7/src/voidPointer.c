#include <stdio.h>

int main()
{
    int integerValue = 20;
    double doubleValue = 3.14;
    char charValue = 'A';
    int x = 10;
    void *ptr = &x;
    // int value = *ptr; // Error, cannot dereference void pointer directly
    int value = *(int *)ptr; // Correct, explicit casting is required
    printf("x: %d\n",value);

    int a[2] = { 1, 2 };
    void* gptr = &a;
    gptr = gptr + sizeof(int);
    printf("Second Array Element: %d\n", *(int*)gptr);

    // Using void pointers to store addresses of different data types
    void *genericPtr;

    genericPtr = &integerValue;
    printf("Integer value: %d\n", *(int *)genericPtr);

    genericPtr = &doubleValue;
    printf("Double value: %lf\n", *(double *)genericPtr);

    genericPtr = &charValue;
    printf("Char value: %c\n", *(char *)genericPtr);

    return 0;
}