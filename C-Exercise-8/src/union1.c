#include <stdio.h>

struct xyz
{
    int a;
    char b;
};

union abc
{
    int a;
    char b;
};

int main()
{
    struct xyz svar;
    union abc var;
    printf("Addresses of svar a and b: %x, %x\n",&svar.a,&svar.b);
    printf("Addresses of var a and b: %x, %x\n",&var.a,&var.b);
    var.a = 65;
    printf("a: %d\n", var.a);
    printf("b: %c\n", var.b);
    return 0;
}