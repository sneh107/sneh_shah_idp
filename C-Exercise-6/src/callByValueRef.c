#include <stdio.h>

void callByValue(int x)
{
    x = x * 2;
    printf("Inside Call by Value - x: %d\n", x);
}
void callByReference(int *y)
{
    *y = *y * 2;
    printf("Inside Call by Reference - *y: %d\n", *y);
}

int main()
{
    int num1 = 5;
    int num2 = 8;

    printf("Before Call by Value - num1: %d\n", num1);
    callByValue(num1);
    printf("After Call by Value - num1: %d\n", num1);

    printf("\nBefore Call by Reference - num2: %d\n", num2);
    callByReference(&num2);
    printf("After Call by Reference - num2: %d\n", num2);

    return 0;
}