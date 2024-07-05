#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *directories[] = {"a", "b", "c", "d", "e"};

int main()
{
    for (int i = 0; i < 5; i++)
    {
        if (mkdir(directories[i], 0777) == -1)
        {
            perror("Error creating directory");
        }
        else
        {
            printf("Directory %s created successfully\n", directories[i]);
        }
    }

    return 0;
}
