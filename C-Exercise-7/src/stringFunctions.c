#include <stdio.h>
#include <string.h>

int main()
{
    char str1[] = "Hello";
    char str2[20];

    printf("Length of str1: %ld\n", strlen(str1));

    strcpy(str2, str1);
    printf("str2 after strcpy: %s\n", str2);

    strcat(str2, " World");
    printf("str2 after strcat: %s\n", str2);

    int cmpResult = strcmp(str1,str2);
    printf("Comparison result: %d\n", cmpResult);

    return 0;
}