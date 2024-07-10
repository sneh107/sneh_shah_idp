/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file parent_child_grandchild.c
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
 * @brief Main function to create a child and a grandchild process and manage their execution.
 *
 * The function forks a child process, which in turn forks a grandchild process.
 * The parent process waits for the child to complete, and the child waits for the grandchild to complete.
 *
 * @return int Returns 0 on successful completion, or 1 if any fork fails.
 */

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
