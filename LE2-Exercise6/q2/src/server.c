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
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define PORT 8081
#define BUFFER_SIZE 1024
#define TIMEOUT 120

char file_list[BUFFER_SIZE];

/**
 * @brief Scans a directory and generates a list of files.
 *
 * @param directory Path to the directory to be scanned.
 */

void scan_directory(const char *directory)
{
    DIR *dir;
    struct dirent *entry;
    file_list[0] = '\0'; // Initialize the file list

    if ((dir = opendir(directory)) != NULL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            char filepath[BUFFER_SIZE];
            snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                strcat(file_list, entry->d_name);
                strcat(file_list, "\n");
            }
        }
        closedir(dir);
    }
    else
    {
        perror("Could not open directory");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sends the generated file list to the client.
 *
 * @param client_fd File descriptor of the client socket.
 */

void send_file_list(int client_fd)
{
    if (send(client_fd, file_list, strlen(file_list), 0) < 0)
    {
        perror("Send failed");
    }
}

/**
 * @brief Sends the specified file to the client.
 *
 * @param client_fd File descriptor of the client socket.
 * @param filename Name of the file to be sent.
 * @param directory Directory where the file is located.
 */

void send_file(int client_fd, const char *filename, const char *directory)
{
    char filepath[BUFFER_SIZE];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    FILE *file = fopen(filepath, "rb");
    if (file == NULL)
    {
        perror("File not found");
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        if (send(client_fd, buffer, bytes_read, 0) < 0)
        {
            perror("Send failed");
            break;
        }
    }

    fclose(file);
}

/**
 * @brief Sends the metadata of the specified file to the client.
 *
 * @param client_fd File descriptor of the client socket.
 * @param filename Name of the file to fetch metadata for.
 * @param directory Directory where the file is located.
 */

void send_file_metadata(int client_fd, const char *filename, const char *directory)
{
    char filepath[BUFFER_SIZE];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    struct stat file_stat;
    if (stat(filepath, &file_stat) < 0)
    {
        perror("File not found");
        return;
    }

    char metadata[BUFFER_SIZE];
    snprintf(metadata, sizeof(metadata),
             "Size: %ld bytes\nType: %s\nCreation date: %s",
             file_stat.st_size,
             (S_ISREG(file_stat.st_mode)) ? "Regular file" : "Other",
             ctime(&file_stat.st_ctime));

    if (send(client_fd, metadata, strlen(metadata), 0) < 0)
    {
        perror("Send failed");
    }
}

/**
 * @brief Handles communication with a connected client.
 *
 * @param client_fd File descriptor of the client socket.
 * @param directory Directory to scan for files.
 */

void handle_client(int client_fd, const char *directory)
{
    char buffer[BUFFER_SIZE];
    fd_set read_fds;
    struct timeval timeout;

    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(client_fd, &read_fds);

        timeout.tv_sec = TIMEOUT;
        timeout.tv_usec = 0;

        int activity = select(client_fd + 1, &read_fds, NULL, NULL, &timeout);

        if (activity == 0)
        {
            printf("Client timed out.\n");
            break;
        }
        else if (activity < 0)
        {
            perror("Select error");
            break;
        }

        if (FD_ISSET(client_fd, &read_fds))
        {
            memset(buffer, 0, BUFFER_SIZE);
            int recv_bytes = recv(client_fd, buffer, BUFFER_SIZE, 0);
            if (recv_bytes < 0)
            {
                perror("recv failed");
                break;
            }
            else if (recv_bytes == 0)
            {
                printf("Client disconnected.\n");
                break;
            }

            if (strncmp(buffer, "LIST", 4) == 0)
            {
                send_file_list(client_fd);
            }
            else if (strncmp(buffer, "GET ", 4) == 0)
            {
                char *filename = buffer + 4;
                send_file(client_fd, filename, directory);
            }
            else if (strncmp(buffer, "META ", 5) == 0)
            {
                char *filename = buffer + 5;
                send_file_metadata(client_fd, filename, directory);
            }
            else if (strncmp(buffer, "QUIT", 4) == 0)
            {
                printf("Client requested to quit.\n");
                break;
            }
            else
            {
                printf("Unknown command: %s\n", buffer);
            }
        }
    }

    close(client_fd);
}

/**
 * @brief Main function for the server.
 *
 * @return int Returns 0 upon successful execution.
 */

int main()
{
    const char *directory = ".";
    scan_directory(directory);

    int server_fd, client_fd;
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
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Accept failed");
            continue;
        }

        printf("Client connected.\n");

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("Fork failed");
            close(client_fd);
        }
        else if (pid == 0)
        {
            close(server_fd);
            handle_client(client_fd, directory);
            exit(0);
        }
        else
        {
            close(client_fd);
        }
    }

    close(server_fd);
    return 0;
}
