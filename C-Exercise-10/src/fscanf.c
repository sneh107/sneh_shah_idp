#include <stdio.h>

int main()
{
    FILE *fp = fopen("myFile.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // int num, result;
    char name[50];

    // Use fscanf to read an integer and a string separately
    while (fscanf(fp, "%*d %s", name) == 1)
    {
        // getchar();
        // printf("Number: %d\n", num);
        printf("Name: %s\n", name);
    }

    // Print the read values
    // printf("Result: %d\n", result);

    fclose(fp);
    return 0;
}