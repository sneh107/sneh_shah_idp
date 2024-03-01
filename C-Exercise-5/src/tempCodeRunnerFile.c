#include <stdio.h>

int main() {
    int m = 5, n;
    n = m++ + ++m + m++ + ++m;
    // After this, m = 9, n = 28

    printf("m=%d n=%d\n", m, n);

    return 0;
}