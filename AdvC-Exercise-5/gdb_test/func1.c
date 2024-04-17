#include <stdio.h>
void func2();

void func1()
{
    int func1_var = 20;
    printf("Func1 Variable: %d\n", func1_var);
    func2();
}