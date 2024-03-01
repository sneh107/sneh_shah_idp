#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, num, flag = 1;

    printf("Enter a Number: ");
    scanf("%d", &num);

    if (num <= 1)
    {
        printf("Not Prime nor Composite\n");
        exit(0);
    }

    for (i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            flag = 0;
            break;
        }
    }

    if (flag)
        printf("%d is Prime!\n", num);
    else
        printf("%d is not a Prime!\n", num);

    return 0;
}