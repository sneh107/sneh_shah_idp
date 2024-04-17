#include <stdio.h>
#include <stdlib.h>

void func1();
void func2();
void func3();

int main()
{
    int main_var = 10;
    // int *ptr=NULL;
    // *ptr = 20;
    printf("Main Variable: %d\n", main_var);
    func1();
    return 0;
}
