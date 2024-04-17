#include <stdio.h>

void func3()
{
    int func3_var = 40;
    printf("Func3 Variable: %d\n", func3_var);
}

void func2()
{
    int func2_var = 30;
    printf("Func2 Variable: %d\n", func2_var);
    func3();
}