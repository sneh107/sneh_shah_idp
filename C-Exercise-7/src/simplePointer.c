#include <stdio.h>

int main()
{
    int num = 10;
    int* ptr;
    ptr = &num;

    printf("Value at ptr = %p \n", ptr);
    printf("Value at num = %d \n", num);
    printf("Value at *ptr = %d \n", *ptr);
    return 0;
}