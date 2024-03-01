#include <stdio.h>

int main()
{
    char str[100];
    FILE *fp = fopen("myFile.txt", "a+");

    // rewind(fp);
    while (fgets(str, sizeof(str), fp) != NULL)
    {
        printf("Line: %s", str);
    }

    fputs("Namaste Bharat\n", fp);
    rewind(fp);
    while (fgets(str, sizeof(str), fp) != NULL)
    {
        printf("Lineu: %s", str);
    }

    fclose(fp);
    return 0;
}

// or
// #include <stdio.h>

// int main()
// {
//     char str[100];
//     FILE *fp = fopen("myFile.txt", "a+");

//     // rewind(fp);
//     while (fgets(str, sizeof(str), fp) != NULL)
//     {
//         printf("Line: %s", str);
//     }

//     fputs("Namaste Bharat\n", fp);
//     fclose(fp);
//     fp = fopen("myFile.txt", "r");

//     while (fgets(str, sizeof(str), fp) != NULL)
//     {
//         printf("Lineu: %s", str);
//     }

//     fclose(fp);
//     return 0;
// }