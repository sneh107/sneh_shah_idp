#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}
int sub(int a, int b)
{
    return a - b;
}

void calculate(int a, int b, int (*fptr)(int, int))
{
    int result;
    result = fptr(a, b);
    printf("%d\n", result);
}

int main()
{
    int a, b;

    printf("Enter number: ");
    scanf("%d", &a);

    printf("Enter number: ");
    scanf("%d", &b);

    calculate(a, b, sub);

    return 0;
}