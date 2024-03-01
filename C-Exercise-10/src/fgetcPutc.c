#include <stdio.h>

int main()
{
    int character;
    char str[] = "4 xyz";
    FILE *fp = fopen("myFile.txt", "a+");

    for (int i = 0; str[i] != '\0'; i++)
    {
        fputc(str[i], fp);
    }

    rewind(fp);

    while ((character = fgetc(fp)) != EOF)
    {
        putchar(character);
    }
    fclose(fp);

    return 0;
}