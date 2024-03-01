#include <stdio.h>
#include <string.h>

int main()
{
    printf("\n");
    char str[] = "Hello world";
    char str1[50];
    char str2[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    
    printf("Enter string : ");
    // scanf("%[^\n]s",str1);
    // puts(str1);
    // gets(str1);
    // puts(str1);
    fgets(str1,sizeof(str1),stdin);
    puts(str1);

    //error cant update like this directly
    // puts(str);
    // str[]="update";
    // puts(str);
    printf("Previous str: %s\n",str);
    strcpy(str,"update");
    printf("Updated str: ");
    puts(str);
    
    return 0;
}