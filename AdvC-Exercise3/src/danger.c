#include <stdio.h>
#include <stdlib.h>

void memory_alloc(int size);

int main()
{
    while (1)
        memory_alloc(1000); // Not freeing Allocated Memory //Program may Crash

    return 0;
}

void memory_alloc(int size)
{
    int *a = malloc(size);
}