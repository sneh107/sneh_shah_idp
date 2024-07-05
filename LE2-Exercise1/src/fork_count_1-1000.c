#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int flag = -1;
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child : This is the child process(pid %d)\n", getpid());
        for (int i = 1; i <= 1000; i++)
        {
            printf("%d\n", i);
        }
        flag = 1;
        // exit(0);
    }
    else
    {
        printf("parent process pid = %d\n", getpid());
        int status;
        wait(&status); // Wait for child process to complete
        // if (WIFEXITED(status))
        // {
        //     printf("Child process completed with exit status %d\n", WEXITSTATUS(status));
        // }
        // else
        // {
        //     printf("Child process did not complete successfully\n");
        // }
        flag = 0;
    }
    printf("%s: Exiting...\n", ((flag == 0) ? "Parent" : "Child"));

    return 0;
}
