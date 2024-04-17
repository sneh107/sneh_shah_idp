#include <stdio.h>

int main()
{

    // char arr[3][10] = {"Sneh", "Shah", "Adityanath"}; // Memory Wastage

    char *arr[3] = {"Sneh", "Shah", "Adityanath"};

    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", arr[i]);
    }

    return 0;
}