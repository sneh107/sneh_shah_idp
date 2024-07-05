#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_sigusr1(int sig)
{
    printf("Child received SIGUSR1\n");
}

void handle_sigusr2(int sig)
{
    printf("Child received SIGUSR2\n");
}

void handle_sigint(int sig)
{
    printf("Child received SIGINT\n");
}

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