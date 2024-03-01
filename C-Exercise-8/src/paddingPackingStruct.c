// #pragma pack(1)
#include <stdio.h>

struct abc
{
    char a[5];
    int c;
    // char b;
};//or }__attribute((packed))__;

int main()
{
    struct abc var;
    printf("%d\n", sizeof(var));
    return 0;
}