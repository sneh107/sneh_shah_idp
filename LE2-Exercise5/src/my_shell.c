#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

void ReadLine(char *line)
{
    if (fgets(line, MAX_LINE, stdin) == NULL)
    {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    size_t length = strlen(line);
    if (line[length - 1] == '\n')
    {
        line[length - 1] = '\0';
    }
}

void ParseLine(char *line, char **args)
{
    int i = 0;
    args[i] = strtok(line, " ");
    while (args[i] != NULL)
    {
        args[++i] = strtok(NULL, " ");
    }
}

void ExecuteCommand(char **args)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

int IsQuit(char **args)
{
    if (strcmp(args[0], "quit") == 0)
    {
        return 1;
    }
    return 0;
}

int main()
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1)
    {
        printf("mysh> ");

        ReadLine(line);

        ParseLine(line, args);

        if (args[0] == NULL)
        {
            continue;
        }

        if (IsQuit(args))
        {
            break;
        }

        ExecuteCommand(args);
    }

    return 0;
}