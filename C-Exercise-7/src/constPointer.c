#include <stdio.h>

int main() {
    int x = 10;
    const int *ptr = &x;  // Pointer to a constant integer
    printf("%d\n",*ptr);

    // Cannot modify the value through the pointer
    // *ptr = 99;  // Error

    // Can change the pointer itself
    int y = 20;
    ptr = &y;
    printf("%d\n",*ptr);

    int z = 30;
    int *const ptr1 = &z;
    printf("%d\n",*ptr1);

    // Can modify the value through the pointer
    *ptr1 = 40;
    printf("%d\n",*ptr1);

    // Cannot change the pointer itself
    // int z = 100;
    // ptr1 = &z;  // Error

    return 0;
}