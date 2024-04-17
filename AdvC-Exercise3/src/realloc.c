#include <stdio.h>
#include <stdlib.h>

int main()
{
    int index = 0, i = 0;
    int *ages;

    ages = (int *)malloc(sizeof(int));

    if (ages == NULL)
    {
        printf("Memory cannot be allocated\n");
    }
    else
    {
        printf("Memory has been successfully allocated\n");
        printf("Base address of ages: %p\n", ages);

        int ans;
        do
        {
            printf("Enter age: ");
            scanf("%d", &ages[index]);
            printf("Would you like to add more ages? (1/0): ");
            scanf("%d", &ans);

            if (ans == 1)
            {
                index++;
                ages = (int *)realloc(ages, (index + 1) * sizeof(int));
                if (ages == NULL)
                {
                    printf("Memory cannot be allocated\n");
                }
                else
                {
                    printf("Memory has been successfully reallocated\n");
                    printf("Base address of ages: %p\n", ages);
                }
            }
        } while (ans == 1);

        printf("Ages entered:\n");
        for (i = 0; i <= index; i++)
        {
            printf("Age %d: %d\n", i, ages[i]);
        }

        free(ages);
    }

    return 0;
}
