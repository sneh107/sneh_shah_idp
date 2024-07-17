/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file server_main.c
 * @brief Main server program for a chat application.
 *
 * This file contains the main entry point for the chat server. It initializes
 * the server socket, binds it to a specified port, listens for incoming client connections,
 * handles client acceptance, and manages client threads for communication.
 * Signal handling for server shutdown is also implemented.
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

#include "../inc/server.h"

int main()
{
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    signal(SIGINT, SignalHandler);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("=== WELCOME TO THE CHAT SERVER ===\n");

    while (server_running)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            if (!server_running)
            {
                break;
            }
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        Client_node_t *cli = (Client_node_t *)malloc(sizeof(Client_node_t));
        cli->sock = new_socket;
        cli->connected_to = -1;
        cli->next = NULL;

        AddClient(cli);

        pthread_t tid;
        pthread_create(&tid, NULL, HandleClient, (void *)cli);
        pthread_detach(tid); // Detach thread to prevent memory leaks
    }

    close(server_fd);
    FreeAllClients();
    printf("\nServer shut down.\n");

    return 0;
}
