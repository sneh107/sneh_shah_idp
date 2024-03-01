#include <stdio.h>

enum boolean
{
    false,
    true
};

enum boolean isEven(int n)
{
    if (n % 2 == 0)
        return true;
    else
        return false;
}

int main()
{
    int num = 5, result;

    result = isEven(num);

    if (result)
    {
        printf("%d is even!", num);
    }
    else
    {
        printf("%d is odd!", num);
    }

    return 0;
}