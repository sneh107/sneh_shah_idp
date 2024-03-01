#include <stdio.h>

int abc(int n)
{
    printf("%d\n", n);
    printf("Hello World\n");
    return n;
}

int main()
{
    // abc();
    int (*fptr)(int) = &abc; // or just abc
    int result;
    result = (*fptr)(5); // or just fptr(5)
    printf("result is %d\n", result);
    return 0;
}