/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file my_shell.c
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Jun/19/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

/**
 * @brief Reads a line of input from stdin.
 * 
 * @param line Buffer to store the read line.
 * @return int Returns 1 on success, 0 on failure.
 */

int ReadLine(char *line)
{
    if (fgets(line, MAX_LINE, stdin) == NULL)
    {
        perror("fgets");
        return 0;
    }

    size_t length = strlen(line);
    if (line[length - 1] == '\n')
    {
        line[length - 1] = '\0';
    }
    return 1;
}

/**
 * @brief Parses a line into individual arguments.
 * 
 * @param line Line of input to be parsed.
 * @param args Array to store parsed arguments.
 * @return int Returns number of arguments parsed.
 */

int ParseLine(char *line, char **args)
{
    int i = 0;
    args[i] = strtok(line, " ");
    while (args[i] != NULL)
    {
        args[++i] = strtok(NULL, " ");
    }
    return i;
}

/**
 * @brief Executes a command with arguments.
 * 
 * @param args Array containing the command and its arguments.
 * @return int Returns 1 on success, 0 on failure.
 */

int ExecuteCommand(char **args)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 0;
    }

    if (pid == 0)
    {
        execvp(args[0], args);
        perror("execvp");
        return 0;
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    return 1;
}

/**
 * @brief Checks if the command is 'quit'.
 * 
 * @param args Array containing the command and its arguments.
 * @return int Returns 1 if the command is 'quit', otherwise 0.
 */

int IsQuit(char **args)
{
    if (strcmp(args[0], "quit") == 0)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Main function where the shell operates.
 * 
 * @return int Returns 0 upon successful execution.
 */

int main()
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1)
    {
        printf("mysh> ");

        if (!ReadLine(line))
        {
            continue;
        }

        int numArgs = ParseLine(line, args);

        if (numArgs == 0)
        {
            continue;
        }

        if (IsQuit(args))
        {
            break;
        }

        if (!ExecuteCommand(args))
        {
            continue;
        }
    }

    return 0;
}

