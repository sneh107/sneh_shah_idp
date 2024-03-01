#include <stdio.h>

int main()
{
    char choice = 2;
    switch (choice)
    {
    case 1 ... 3:
        printf("1\n");
        break;

    case 4:
        printf("2\n");
        break;

    default:
        printf("Invalid Operator Input\n");
    }
    return 0;
}