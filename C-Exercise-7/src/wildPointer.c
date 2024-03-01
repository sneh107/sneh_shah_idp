#include <stdio.h>

int main() {
    int *wildPtr;  // Declaration of a wild pointer

    printf("%d\n", *wildPtr); //Segmentation fault (core dumped)

    return 0;
}