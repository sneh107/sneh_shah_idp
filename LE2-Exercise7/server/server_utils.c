/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file server_utils.c
 * @brief Utility functions for managing clients and server operations in a chat application.
 *
 * This file provides various utility functions for handling client connections,
 * disconnections, client list management, name validation, and server shutdown handling.
 * It includes functions to add and remove clients from a linked list, list connected clients,
 * check if client names are unique, broadcast server shutdown messages, and handle server signals.
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
