#include <stdio.h>

int global_var_initialized = 10;
int global_var_uninitialized;

int main()
{
    static int static_var = 20;
    int local_var = 30;

    printf("Address of global_var_initialized: %p\n", &global_var_initialized);
    printf("Address of global_var_uninitialized: %p\n", &global_var_uninitialized);
    printf("Address of static_var: %p\n", &static_var);
    printf("Address of local_var: %p\n", &local_var);

    return 0;
}