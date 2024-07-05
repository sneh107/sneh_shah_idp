#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1 = fork();

    if (pid1 < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid1 == 0)
    {
        printf("First child: PID = %d, PPID = %d\n", getpid(), getppid());

        pid_t pid2 = fork();
        if (pid2 < 0)
        {
            perror("Fork failed");
            return 1;
        }
        else if (pid2 == 0)
        {
            printf("Grandchild: PID = %d, PPID = %d\n", getpid(), getppid());
            exit(0);
        }
        else
        {
            wait(NULL);
            exit(0);
        }
    }
    else
    {
        printf("Parent: PID = %d, PPID = %d\n", getpid(), getppid());
        wait(NULL);
    }

    return 0;
}
