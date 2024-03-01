#include <stdio.h>

int main() {
    int threeDArray[3][3][4] = {
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        },
        {
            {13, 14, 15, 16},
            {17, 18, 19, 20},
            {21, 22, 23, 24}
        },
        {
            {25, 26, 27, 28},
            {29, 30, 31, 32},
            {33, 34, 35, 36}
        }
    };

    for (int layer = 0; layer < 3; layer++) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 4; col++) {
                printf("%d\t", threeDArray[layer][row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}