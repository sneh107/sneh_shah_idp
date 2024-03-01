#include <stdio.h>
int main()
{
    int c,d;
    //    printf("%d\n",c);

    printf("Enter a Character :");
    c = getchar();
    printf("getchar returned: %d\n",c);

    printf("You entered: ");
    d=putchar(c);
    printf("\n");
    printf("putchar returned: %d\n",d);

    return 0;
}