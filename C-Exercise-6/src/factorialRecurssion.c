#include <stdio.h>

int fact(int num)
{
    if (num == 1)
        return 1;
    else
        return num * fact(num - 1);
}

int main()
{
    int num = 4, result;
    result = fact(num);
    printf("Factorial of %d = %d\n", num, result);
    return 0;
}