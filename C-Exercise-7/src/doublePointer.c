#include <stdio.h>

int main() {
    int x = 10;
    int *ptr1 = &x;   
    int **ptr2 = &ptr1;  
    printf("Value of x: %d\n", **ptr2);

    **ptr2 = 20;
    printf("Updated value of x: %d\n", x);
    return 0;
}