#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>

#define PORT 7777
#define BUFFER_SIZE 1024
#define NAME_LEN 32

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

void AddClient(Client_node_t *client)
{
    pthread_mutex_lock(&clients_mutex);
    client->next = clients_head;
    clients_head = client;
    printf("Client connected: %s\n", client->name);
    pthread_mutex_unlock(&clients_mutex);
}

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
    send(sock, list, strlen(list), 0);
    pthread_mutex_unlock(&clients_mutex);
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

void *HandleClient(void *arg)
{
    char buffer[BUFFER_SIZE];
    char name[NAME_LEN];
    int leave_flag = 0;
    Client_node_t *cli = (Client_node_t *)arg;

    while (1)
    {
        memset(name, '\0', sizeof(name));
        if (recv(cli->sock, name, NAME_LEN, 0) <= 0 || strlen(name) < 2 || strlen(name) >= NAME_LEN - 1)
        {
            printf("Enter the name correctly.\n");
            send(cli->sock, "Enter the name correctly: ", 26, 0);
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
                send(cli->sock, "Name is already taken. Enter a different name: ", 47, 0);
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
                    send(cli->sock, "You are already connected to someone.\n", 38, 0);
                }
                else
                {
                    char target_name[NAME_LEN];
                    sscanf(buffer + 8, "%s", target_name);

                    if (strcmp(target_name, cli->name) == 0)
                    {
                        send(cli->sock, "You cannot connect to yourself.\n", 32, 0);
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
                                send(cli->sock, msg, strlen(msg), 0);
                                snprintf(msg, BUFFER_SIZE, "You are now connected to %s\n", cli->name);
                                send(temp->sock, msg, strlen(msg), 0);
                                printf("\n*** %s connected to %s ***\n", cli->name, temp->name);
                                break;
                            }
                            temp = temp->next;
                        }
                        if (!found)
                        {
                            send(cli->sock, "Connection failed.\n", 19, 0);
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
                            send(temp->sock, "*** You have been disconnected ***\n", 35, 0);
                            printf("\n*** %s disconnected from %s ***\n", cli->name, temp->name);
                            break;
                        }
                        temp = temp->next;
                    }
                    cli->connected_to = -1;
                    send(cli->sock, "*** You have been disconnected ***\n", 35, 0);
                }
                else
                {
                    send(cli->sock, "You are not connected to anyone.\n", 33, 0);
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
                            send(temp->sock, "*** You have been disconnected ***\n", 35, 0);
                            break;
                        }
                        temp = temp->next;
                    }
                    cli->connected_to = -1;
                    send(cli->sock, "*** You have been disconnected ***\n", 35, 0);
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
                    send(cli->connected_to, formatted_msg, strlen(formatted_msg), 0);
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
                    send(cli->sock, "You are not connected to anyone.\n", 33, 0);
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
                        send(temp->sock, "*** You have been disconnected ***\n", 35, 0);
                        break;
                    }
                    temp = temp->next;
                }
                cli->connected_to = -1;
                send(cli->sock, "*** You have been disconnected ***\n", 35, 0);
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

void BroadcastShutdownMessage()
{
    pthread_mutex_lock(&clients_mutex);
    Client_node_t *temp = clients_head;
    while (temp != NULL)
    {
        send(temp->sock, "Server is shutting down.\n", 25, 0);
        close(temp->sock);
        temp = temp->next;
    }
    pthread_mutex_unlock(&clients_mutex);
}

void SignalHandler(int sig)
{
    if (sig == SIGINT)
    {
        server_running = 0;
        BroadcastShutdownMessage();
        close(server_fd);
    }
}

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
