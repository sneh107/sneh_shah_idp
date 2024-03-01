#include <stdio.h>

struct date
{
    int d : 5;
    int m : 4;
    int y;
};

int main()
{
    struct date d = {10, 7, 2003};
    struct date d1 = {28, 11, 2000};
    printf("%d-%d-%d\n", d.d, d.m, d.y);
    printf("%d-%d-%d\n", d1.d, d1.m, d1.y);
    // printf("%ld\n", sizeof(d));
    return 0;
}