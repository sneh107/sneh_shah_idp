#include <stdio.h>

int main()
{
    char ch;
    printf("Enter char: ");
    scanf("%c", &ch);

    if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
    {
        printf("Char is a Vowel\n");
    }
    else
    {
        printf("Not a Vowel\n");
    }
}