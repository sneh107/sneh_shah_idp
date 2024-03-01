#include <stdio.h>

int main()
{
    FILE *fp = fopen("myFile.txt", "r");
    int character;

    while ((character = fgetc(fp)) != EOF)
    {
        putchar(character);
    }

    if (feof(fp))
    {
        printf("End of file reached!\n");
    }
    else
    {
        printf("Something went wrong!\n");
    }

    fclose(fp);
    return 0;
}