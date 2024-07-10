/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file fork_count_1-1000.c
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * May/28/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @brief Main function to create a child process and manage its execution.
 *
 * The function forks a child process. The child process prints numbers from 1 to 1000,
 * while the parent process waits for the child to complete.
 *
 * @return int Returns 0 on successful completion, or 1 if fork fails.
 */

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
