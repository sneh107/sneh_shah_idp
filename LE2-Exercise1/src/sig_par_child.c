/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file sig_par_child.c
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * May/29/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Signal handler for SIGUSR1.
 *
 * This function is called when the SIGUSR1 signal is received by the child process.
 *
 * @param sig The signal number.
 */

void handle_sigusr1(int sig)
{
    printf("Child received SIGUSR1\n");
}

/**
 * @brief Signal handler for SIGUSR2.
 *
 * This function is called when the SIGUSR2 signal is received by the child process.
 *
 * @param sig The signal number.
 */

void handle_sigusr2(int sig)
{
    printf("Child received SIGUSR2\n");
}

/**
 * @brief Signal handler for SIGINT.
 *
 * This function is called when the SIGINT signal is received by the child process.
 *
 * @param sig The signal number.
 */

void handle_sigint(int sig)
{
    printf("Child received SIGINT\n");
}

/**
 * @brief Main function to create a child process and send signals to it.
 *
 * The function forks a child process. The child process sets up signal handlers for
 * SIGUSR1, SIGUSR2, and SIGINT, and waits for these signals. The parent process sends
 * these signals to the child and waits for the child to terminate.
 *
 * @return int Returns 0 on successful completion, or exits with EXIT_FAILURE if fork fails.
 */

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        signal(SIGUSR1, handle_sigusr1);
        signal(SIGUSR2, handle_sigusr2);
        signal(SIGINT, handle_sigint);

        pause(); // Wait for the first signal
        pause(); // Wait for the second signal
        pause(); // Wait for the third signal

        printf("Child process exiting\n");
        // exit(0);
    }
    else
    {
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

        sleep(1); // Sleep to ensure child process has set up signal handlers
        kill(pid, SIGUSR1);
        sleep(1);
        kill(pid, SIGUSR2);
        sleep(1);
        kill(pid, SIGINT);

        wait(NULL);
        printf("Parent process: Child terminated\n");
    }

    return 0;
}
