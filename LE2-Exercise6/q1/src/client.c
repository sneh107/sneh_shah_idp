/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file client.c
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
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

/**
 * @brief Main function for the client application.
 *
 * @return int Returns 0 upon successful execution.
 */

int main()
{
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    char *quit_cmd = "quit";

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        clock_t start_time = clock();

        if (send(sock, buffer, strlen(buffer), 0) < 0)
        {
            perror("Send failed");
            close(sock);
            exit(EXIT_FAILURE);
        }

        if (strncmp(buffer, quit_cmd, strlen(quit_cmd)) == 0)
        {
            printf("Client sent quit command. Shutting down.\n");
            break;
        }

        memset(buffer, 0, BUFFER_SIZE);

        int recv_bytes = recv(sock, buffer, BUFFER_SIZE, 0);
        if (recv_bytes < 0)
        {
            perror("recv failed");
            close(sock);
            exit(EXIT_FAILURE);
        }

        clock_t end_time = clock();
        double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("Server response: %s\n", buffer);
        printf("Round trip time: %f seconds\n", total_time);
    }

    close(sock);
    return 0;
}
