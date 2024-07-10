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
 * Jul/01/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>

#define PORT 7777
#define BUFFER_SIZE 1024
#define NAME_LEN 32

/**
 * @struct Client_node_t
 * @brief Represents a node in the client list.
 */
typedef struct client_node
{
    int sock;
    char name[NAME_LEN];
    int connected_to;
    struct client_node *next;
} Client_node_t;

Client_node_t *clients_head = NULL;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
int server_running = 1;
int server_fd;

/**
 * @brief Adds a new client to the linked list of clients.
 *
 * @param client Pointer to the client node to be added.
 */
void AddClient(Client_node_t *client)
{
    pthread_mutex_lock(&clients_mutex);
    client->next = clients_head;
    clients_head = client;
    printf("Client connected: %s\n", client->name);
    pthread_mutex_unlock(&clients_mutex);
}

/**
 * @brief Removes a client from the linked list of clients based on its socket file descriptor.
 *
 * @param sock Socket file descriptor of the client to be removed.
 */
void RemoveClient(int sock)
{
    pthread_mutex_lock(&clients_mutex);
    Client_node_t *temp = clients_head, *prev = NULL;
    while (temp != NULL && temp->sock != sock)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL)
    {
        if (prev == NULL)
        {
            clients_head = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }
        printf("Client disconnected: %s\n", temp->name);
        free(temp);
    }
    pthread_mutex_unlock(&clients_mutex);
}

/**
 * @brief Frees all memory used by the linked list of clients.
 */
void FreeAllClients()
{
    pthread_mutex_lock(&clients_mutex);
    Client_node_t *temp = clients_head;
    while (temp != NULL)
    {
        Client_node_t *next = temp->next;
        close(temp->sock);
        free(temp);
        temp = next;
    }
    clients_head = NULL;
    pthread_mutex_unlock(&clients_mutex);
}

/**
 * @brief Sends a list of connected client names to a specific client.
 *
 * @param sock Socket file descriptor of the client to send the list to.
 */
void ListClients(int sock)
{
    pthread_mutex_lock(&clients_mutex);
    char list[BUFFER_SIZE] = "Connected clients:\n";
    Client_node_t *temp = clients_head;
    while (temp != NULL)
    {
        strncat(list, temp->name, NAME_LEN);
        strcat(list, "\n");
        temp = temp->next;
    }
    if (send(sock, list, strlen(list), 0) < 0) {
        perror("send");
    }
    pthread_mutex_unlock(&clients_mutex);
}

/**
 * @brief Removes newline characters from a string.
 *
 * @param arr The string to process.
 * @param length Length of the string.
 */
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

/**
 * @brief Checks if a given name is unique among all connected clients.
 *
 * @param name Name to check.
 * @return 1 if the name is unique, 0 otherwise.
 */
int IsNameUnique(char *name)
{
    pthread_mutex_lock(&clients_mutex);
    Client_node_t *temp = clients_head;
    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            pthread_mutex_unlock(&clients_mutex);
            return 0; // Name is not unique
        }
        temp = temp->next;
    }
    pthread_mutex_unlock(&clients_mutex);
    return 1; // Name is unique
}

/**
 * @brief Handles communication with a client.
 *
 * @param arg Pointer to the client node structure.
 * @return NULL
 */
void *HandleClient(void *arg)
{
    char buffer[BUFFER_SIZE];
    char name[NAME_LEN];
    int leave_flag = 0;
    Client_node_t *cli = (Client_node_t *)arg;

    while (1)
    {
        memset(name, '\0', sizeof(name));
        int recv_result = recv(cli->sock, name, NAME_LEN, 0);
        if (recv_result <= 0 || strlen(name) < 2 || strlen(name) >= NAME_LEN - 1)
        {
            printf("Enter the name correctly.\n");
            if (send(cli->sock, "Enter the name correctly: ", 26, 0) < 0) {
                perror("send");
            }
        }
        else
        {
            RemoveNewLine(name, NAME_LEN);
            if (IsNameUnique(name))
            {
                strncpy(cli->name, name, NAME_LEN - 1);
                snprintf(buffer, BUFFER_SIZE, "\n*** %s has joined the chat ***\n", cli->name);
                printf("%s", buffer);
                ListClients(cli->sock);
                break;
            }
            else
            {
                if (send(cli->sock, "Name is already taken. Enter a different name: ", 47, 0) < 0) {
                    perror("send");
                }
            }
        }
    }

    memset(buffer, '\0', sizeof(buffer));

    while (1)
    {
        if (leave_flag)
        {
            break;
        }

        int receive = recv(cli->sock, buffer, BUFFER_SIZE, 0);
        if (receive > 0)
        {
            buffer[receive] = '\0';
            RemoveNewLine(buffer, BUFFER_SIZE);

            if (strcmp(buffer, "list") == 0)
            {
                ListClients(cli->sock);
            }
            else if (strncmp(buffer, "connect", 7) == 0)
            {
                if (cli->connected_to != -1)
                {
                    if (send(cli->sock, "You are already connected to someone.\n", 38, 0) < 0) {
                        perror("send");
                    }
                }
                else
                {
                    char target_name[NAME_LEN];
                    sscanf(buffer + 8, "%s", target_name);

                    if (strcmp(target_name, cli->name) == 0)
                    {
                        if (send(cli->sock, "You cannot connect to yourself.\n", 32, 0) < 0) {
                            perror("send");
                        }
                    }
                    else
                    {
                        pthread_mutex_lock(&clients_mutex);
                        int found = 0;
                        Client_node_t *temp = clients_head;
                        while (temp != NULL)
                        {
                            if (strcmp(temp->name, target_name) == 0 && temp->connected_to == -1)
                            {
                                cli->connected_to = temp->sock;
                                temp->connected_to = cli->sock;
                                found = 1;
                                char msg[BUFFER_SIZE];
                                snprintf(msg, BUFFER_SIZE, "You are now connected to %s\n", temp->name);
                                if (send(cli->sock, msg, strlen(msg), 0) < 0) {
                                    perror("send");
                                }
                                snprintf(msg, BUFFER_SIZE, "You are now connected to %s\n", cli->name);
                                if (send(temp->sock, msg, strlen(msg), 0) < 0) {
                                    perror("send");
                                }
                                printf("\n*** %s connected to %s ***\n", cli->name, temp->name);
                                break;
                            }
                            temp = temp->next;
                        }
                        if (!found)
                        {
                            if (send(cli->sock, "Connection failed.\n", 19, 0) < 0) {
                                perror("send");
                            }
                        }
                        pthread_mutex_unlock(&clients_mutex);
                    }
                }
            }
            else if (strcmp(buffer, "disconnect") == 0)
            {
                pthread_mutex_lock(&clients_mutex);
                if (cli->connected_to != -1)
                {
                    Client_node_t *temp = clients_head;
                    while (temp != NULL)
                    {
                        if (temp->sock == cli->connected_to)
                        {
                            temp->connected_to = -1;
                            if (send(temp->sock, "*** You have been disconnected ***\n", 35, 0) < 0) {
                                perror("send");
                            }
                            printf("\n*** %s disconnected from %s ***\n", cli->name, temp->name);
                            break;
                        }
                        temp = temp->next;
                    }
                    cli->connected_to = -1;
                    if (send(cli->sock, "*** You have been disconnected ***\n", 35, 0) < 0) {
                        perror("send");
                    }
                }
                else
                {
                    if (send(cli->sock, "You are not connected to anyone.\n", 33, 0) < 0) {
                        perror("send");
                    }
                }
                pthread_mutex_unlock(&clients_mutex);
            }
            else if (strcmp(buffer, "quit") == 0)
            {
                pthread_mutex_lock(&clients_mutex);
                if (cli->connected_to != -1)
                {
                    Client_node_t *temp = clients_head;
                    while (temp != NULL)
                    {
                        if (temp->sock == cli->connected_to)
                        {
                            temp->connected_to = -1;
                            if (send(temp->sock, "*** You have been disconnected ***\n", 35, 0) < 0) {
                                perror("send");
                            }
                            break;
                        }
                        temp = temp->next;
                    }
                    cli->connected_to = -1;
                    if (send(cli->sock, "*** You have been disconnected ***\n", 35, 0) < 0) {
                        perror("send");
                    }
                }
                snprintf(buffer, BUFFER_SIZE, "\n*** %s has left the chat ***\n", cli->name);
                printf("%s", buffer);
                leave_flag = 1;
                pthread_mutex_unlock(&clients_mutex);
            }
            else
            {
                if (cli->connected_to != -1)
                {
                    char formatted_msg[BUFFER_SIZE + NAME_LEN + 3];
                    snprintf(formatted_msg, sizeof(formatted_msg), "[%s] %s", cli->name, buffer);
                    if (send(cli->connected_to, formatted_msg, strlen(formatted_msg), 0) < 0) {
                        perror("send");
                    }
                    printf("\nServer received from %s: %s\n", cli->name, buffer);
                    Client_node_t *temp = clients_head;
                    while (temp != NULL)
                    {
                        if (temp->sock == cli->connected_to)
                        {
                            printf("Server sent to %s: %s\n", temp->name, formatted_msg);
                            break;
                        }
                        temp = temp->next;
                    }
                }
                else
                {
                    if (send(cli->sock, "You are not connected to anyone.\n", 33, 0) < 0) {
                        perror("send");
                    }
                }
            }
        }
        else if (receive == 0 || strcmp(buffer, "quit") == 0)
        {
            pthread_mutex_lock(&clients_mutex);
            {
                Client_node_t *temp = clients_head;
                while (temp != NULL)
                {
                    if (temp->sock == cli->connected_to)
                    {
                        temp->connected_to = -1;
                        if (send(temp->sock, "*** You have been disconnected ***\n", 35, 0) < 0) {
                            perror("send");
                        }
                        break;
                    }
                    temp = temp->next;
                }
                cli->connected_to = -1;
                if (send(cli->sock, "*** You have been disconnected ***\n", 35, 0) < 0) {
                    perror("send");
                }
            }
            snprintf(buffer, BUFFER_SIZE, "\n*** %s has left the chat ***\n", cli->name);
            printf("%s", buffer);
            leave_flag = 1;
            pthread_mutex_unlock(&clients_mutex);
        }
        else
        {
            printf("ERROR!\n");
            leave_flag = 1;
        }

        memset(buffer, '\0', sizeof(buffer));
    }

    RemoveClient(cli->sock);
    close(cli->sock);
    pthread_exit(NULL);
}

/**
 * @brief Broadcasts a shutdown message to all connected clients.
 */
void BroadcastShutdownMessage()
{
    pthread_mutex_lock(&clients_mutex);
    Client_node_t *temp = clients_head;
    while (temp != NULL)
    {
        if (send(temp->sock, "Server is shutting down.\n", 25, 0) < 0) {
            perror("send");
        }
        close(temp->sock);
        temp = temp->next;
    }
    pthread_mutex_unlock(&clients_mutex);
}

/**
 * @brief Signal handler function to catch SIGINT (Ctrl+C) and initiate server shutdown.
 *
 * @param sig Signal number.
 */
void SignalHandler(int sig)
{
    if (sig == SIGINT)
    {
        server_running = 0;
        BroadcastShutdownMessage();
        close(server_fd);
    }
}

/**
 * @brief Main function where the server initializes, listens for client connections,
 * and manages client interactions.
 *
 * @return 0 on success.
 */
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
        if (cli == NULL)
        {
            perror("malloc");
            close(new_socket);
            continue;
        }
        cli->sock = new_socket;
        cli->connected_to = -1;
        cli->next = NULL;

        AddClient(cli);

        pthread_t tid;
        if (pthread_create(&tid, NULL, HandleClient, (void *)cli) != 0)
        {
            perror("pthread_create");
            RemoveClient(cli->sock);
             close(cli->sock);
            free(cli);
            continue;
        }
        if (pthread_detach(tid) != 0)
        {
            perror("pthread_detach");
            RemoveClient(cli->sock);
            close(cli->sock);
            free(cli);
            continue;
        }
    }

  	close(server_fd);
   	
   
    FreeAllClients();
    printf("\nServer shut down.\n");

    return 0;
}

