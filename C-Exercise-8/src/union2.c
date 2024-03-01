#include <stdio.h>
#include <string.h>

union abc
{
    int i;
    float f;
    char str[20];
};

int main()
{

    union abc var;

    var.i = 10;
    var.f = 20.5;
    strcpy(var.str, "Namaste Bharat");
    printf("Before\n");
    printf("var.i : %d\n", var.i);
    printf("var.f : %f\n", var.f);
    printf("var.str : %s\n", var.str);

    printf("\nAfter\n");
    var.i = 10;
    printf("var.i : %d\n", var.i);

    var.f = 20.5;
    printf("var.f : %f\n", var.f);

    strcpy(var.str, "Hello World");
    printf("var.str : %s\n", var.str);

    return 0;
}