#include <stdio.h>

void fun1(void (*fptr)())
{
    printf("fun1 called\n");
    fptr();
}

void fun2()
{
    printf("fun2 called\n");
}

int main()
{
    fun1(fun2);
    return 0;
}