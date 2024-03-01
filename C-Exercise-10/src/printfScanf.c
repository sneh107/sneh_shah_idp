#include <stdio.h>

int main()
{
    // int num = 10;
    // float pi = 3.14;
    // char str[] = "Hello World";

    int num;
    float pi;
    char str[20];

    printf("Enter int float and a string: ");
    int scanResult = scanf("%d%f %[^\n]s", &num, &pi, str);

    int printedChars = printf("Integer: %d, Float: %f, String: %s\n", num, pi, str);
    printf("printf returned: %d\n", printedChars);
    printf("scanf returned : %d", scanResult);
    return 0;
}