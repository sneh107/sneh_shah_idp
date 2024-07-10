/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file mkdir_sys_call.c
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * May/31/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *directories[] = {"a", "b", "c", "d", "e"};

/**
 * @brief Main function to create directories.
 *
 * The function iterates over the array of directory names and attempts to create each directory
 * with read, write, and execute permissions for the owner, group, and others. It prints a success
 * message for each directory created and an error message if the creation fails.
 *
 * @return int Returns 0 on successful completion.
 */

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
