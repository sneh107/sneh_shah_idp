#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int CalculateSquare(int n)
{
    int square = 0;
    for (int i = 0; i < n; ++i)
    {
        square += n;
    }
    return square;
}

int main()
{
    int pipe_fd[2];
    pid_t pid;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(pipe_fd[0]);

        for (int i = 1; i <= 1000; ++i)
        {
            int square = CalculateSquare(i);
            printf("child writing!\n");
            write(pipe_fd[1], &i, sizeof(int));
            write(pipe_fd[1], &square, sizeof(int));
            usleep(100);
        }

        close(pipe_fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipe_fd[1]);

        for (int i = 1; i <= 1000; ++i)
        {
            int number, square;
            // sleep(1);
            read(pipe_fd[0], &number, sizeof(int));
            read(pipe_fd[0], &square, sizeof(int));
            printf("Parent is reading!\n");
            printf("Square of %d is %d\n", number, square);
        }

        close(pipe_fd[0]);

        wait(NULL);
    }

    return 0;
}
