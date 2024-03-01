#include <stdio.h>

enum week
{
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
} today;

int main()
{
    today = Wednesday;
    printf("Day %d\n", today);
    return 0;
}