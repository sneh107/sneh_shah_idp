#include <stdio.h>

struct child
{
    int x;
    char c;
};

struct parent
{
    int a;
    struct child b;
};

// or in one structure
// struct parent {
//     int a;
//     struct {
//         int x;
//         char c;
//     } b;
// };

int main()
{
    struct parent var1 = {10, 20, 'A'}; // or for nested single struct: struct parent var1 = { 10, {20, 'A'} };
    // or assigning one by one
    // var1.a = 10;
    // var1.b.x = 20;
    // var1.b.c = 'A';
    printf("var1.a = %d\n", var1.a);
    printf("var1.b.x = %d\n", var1.b.x);
    printf("var1.b.c = %c\n", var1.b.c);

    return 0;
}
