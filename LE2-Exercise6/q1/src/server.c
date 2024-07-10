/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file server.c
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Jun/24/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

/**
 * @brief Function to handle communication with a client.
 *
 * @param arg Pointer to the client file descriptor.
 * @return void* Returns NULL when the client connection is closed.
 */

void *HandleClient(void *arg)
{
    int client_fd = *(int *)arg;
    free(arg);
    char buffer[BUFFER_SIZE];
    char *quit_cmd = "quit";

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        int recv_bytes = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (recv_bytes < 0)
        {
            perror("recv failed");
            close(client_fd);
            return NULL;
        }
        else if (recv_bytes == 0)
        {
            printf("Client disconnected.\n");
            break;
        }

        if (strncmp(buffer, quit_cmd, strlen(quit_cmd)) == 0)
        {
            printf("Server received quit command from client. Closing connection.\n");
            break;
        }

        clock_t start_time = clock();

        if (send(client_fd, buffer, strlen(buffer), 0) < 0)
        {
            perror("Send failed");
            close(client_fd);
            return NULL;
        }

        clock_t end_time = clock();
        double processing_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("Processed message: %s\n", buffer);
        printf("Processing time: %f seconds\n", processing_time);
    }

    close(client_fd);
    return NULL;
}

/**
 * @brief Main function for the server application.
 *
 * @return int Returns 0 upon successful execution.
 */

int main()
{
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1)
    {
        int *client_fd = malloc(sizeof(int));
        if ((*client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Accept failed");
            free(client_fd);
            continue;
        }

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, HandleClient, client_fd);
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}
