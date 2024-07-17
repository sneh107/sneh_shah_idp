/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file client_utils.c
 * @brief Utility functions for the client-side chat application.
 *
 * This file contains utility functions used by the client-side application,
 * including printing command guides, removing newlines from strings,
 * handling sending and receiving messages via sockets, and managing user interactions.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Jul/01/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include "../inc/client.h"

void PrintGuide()
{
    printf("\nAvailable commands:\n");
    printf("1. list: Display names of all connected clients\n");
    printf("2. connect <client name>: Connect to another client\n");
    printf("3. disconnect: Disconnect from the current client\n");
    printf("4. quit: Exit the chat application\n\n");
}

void RemoveNewLine(char *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == '\n')
        {
            arr[i] = '\0';
            break;
        }
    }
}

void *SendMessageHandler(void *sock)
{
    int server_sock = *((int *)sock);
    char buffer[BUFFER_SIZE];
    while (1)
    {
        fgets(buffer, BUFFER_SIZE, stdin);
        RemoveNewLine(buffer, BUFFER_SIZE);
        if (send(server_sock, buffer, strlen(buffer), 0) < 0)
        {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }
        if (strcmp(buffer, "quit") == 0)
        {
            close(server_sock);
            exit(EXIT_SUCCESS);
        }
        bzero(buffer, BUFFER_SIZE);
    }
}

void *ReceiveMessageHandler(void *sock)
{
    int server_sock = *((int *)sock);
    char buffer[BUFFER_SIZE];

    while (1)
    {
        int receive = recv(server_sock, buffer, BUFFER_SIZE, 0);
        if (receive > 0)
        {
            buffer[receive] = '\0';
            printf("%s\n", buffer);

            if (strstr(buffer, "You are now connected to") != NULL)
            {
                printf("Type 'disconnect' to disconnect from the current client.\n\n");
            }
            else if (strstr(buffer, "has left") != NULL || strstr(buffer, "disconnected") != NULL)
            {
                PrintGuide();
            }
            else if (strstr(buffer, "Server is shutting down.") != NULL)
            {
                close(server_sock);
                exit(EXIT_SUCCESS);
            }
        }
        else if (receive == 0)
        {
            break;
        }
        else
        {
            perror("Recv failed");
            exit(EXIT_FAILURE);
        }
        bzero(buffer, BUFFER_SIZE);
    }
    pthread_exit(NULL);
}