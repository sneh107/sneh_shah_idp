#include <stdio.h>

int main()
{
    int num;
    printf("Enter an integer: ");
    while (scanf("%d", &num) != 1)
    {
        while (getchar() != '\n');
        printf("Invalid input. Enter an integer: ");
    }

    return 0;
}
