#include <stdio.h>
#include <stdarg.h>

int max(int num, ...)
{
    va_list args;

    va_start(args, num);

    // for (int i = 0; i < num; i++)
    // {
    //     int result = va_arg(args, int);
    //     printf("%d\n", result);
    // }
    // return 0;
    int max;
    for (int i = 0; i < num; i++)
    {
        int result = va_arg(args, int);
        if (i == 0)
            max = result;
        else if (result > max)
            max = result;
    }
    va_end(args);
    return max;
}

int main()
{
    int maxOf = max(4, 10, 40, 20, 30);
    printf("Max = %d\n", maxOf);
    return 0;
}