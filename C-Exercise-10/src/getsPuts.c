#include <stdio.h>

int main() {
    char str[100];

    printf("Enter a string: ");
    gets(str);//char *result = gets(str);

    // printf("%s", result);
    int result=puts(str);
    printf("%d",result);

    return 0;
}