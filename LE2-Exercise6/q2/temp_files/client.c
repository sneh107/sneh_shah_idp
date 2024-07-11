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
 * Jun/25/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

/**
 * @brief Sends "LIST" command to the server and prints the received file list.
 *
 * @param sock Socket file descriptor connected to the server.
 */

void fetch_file_list(int sock)
{
    char buffer[BUFFER_SIZE];

    send(sock, "LIST", strlen("LIST"), 0);
    memset(buffer, 0, BUFFER_SIZE);

    int recv_bytes = recv(sock, buffer, BUFFER_SIZE, 0);
    if (recv_bytes < 0)
    {
        perror("recv failed");
    }
    else
    {
        printf("File list:\n%s\n", buffer);
    }
}

/**
 * @brief Sends "GET <filename>" command to the server and downloads the file.
 *
 * @param sock Socket file descriptor connected to the server.
 * @param filename Name of the file to download.
 */

void fetch_file(int sock, const char *filename)
{
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "GET %s", filename);

    send(sock, buffer, strlen(buffer), 0);
    memset(buffer, 0, BUFFER_SIZE);

    char filepath[BUFFER_SIZE];
    snprintf(filepath, BUFFER_SIZE, "downloaded_%s", filename);
    int file_fd = open(filepath, O_CREAT | O_WRONLY, 0666);

    if (file_fd < 0)
    {
        perror("File open failed");
        return;
    }
    int recv_bytes = 0;
    while ((recv_bytes = recv(sock, buffer, BUFFER_SIZE, 0)) > 0)
    {
        if (strcmp(buffer, "Specified file not found") == 0)
        {
            remove(filepath);
            close(file_fd);
            printf("%s\n", buffer);
            return;
        }

        write(file_fd, buffer, recv_bytes);
        if (recv_bytes < BUFFER_SIZE)
        {
            // write(file_fd, buffer, recv_bytes);
            break;
        }
    }

    if (recv_bytes < 0)
    {
        perror("recv failed");
    }

    close(file_fd);
    printf("File '%s' downloaded successfully.\n", filename);
}

/**
 * @brief Sends "META <filename>" command to the server and prints the received file metadata.
 *
 * @param sock Socket file descriptor connected to the server.
 * @param filename Name of the file to fetch metadata for.
 */

void fetch_file_metadata(int sock, const char *filename)
{
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "META %s", filename);

    send(sock, buffer, strlen(buffer), 0);
    memset(buffer, 0, BUFFER_SIZE);

    int recv_bytes = recv(sock, buffer, BUFFER_SIZE, 0);
    if (recv_bytes < 0)
    {
        perror("recv failed");
    }
    else
    {
        printf("Metadata for file '%s':\n%s\n", filename, buffer);
    }
}

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
    char command[BUFFER_SIZE];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        perror("Invalid address/Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    while (1)
    {
        printf("Enter command (LIST, GET <filename>, META <filename>, QUIT): ");
        fgets(command, BUFFER_SIZE, stdin);

        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "LIST", 4) == 0)
        {
            fetch_file_list(sock);
        }
        else if (strncmp(command, "GET ", 4) == 0)
        {
            char *filename = command + 4;
            fetch_file(sock, filename);
        }
        else if (strncmp(command, "META ", 5) == 0)
        {
            char *filename = command + 5;
            fetch_file_metadata(sock, filename);
        }
        else if (strncmp(command, "QUIT", 4) == 0)
        {
            send(sock, "QUIT", strlen("QUIT"), 0);
            printf("Disconnecting from server.\n");
            break;
        }
        else
        {
            printf("Unknown command.\n");
        }
    }

    close(sock);
    return 0;
}
