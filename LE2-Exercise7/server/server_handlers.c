/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file server_handlers.c
 * @brief Functions for handling client interactions in the server-side chat application.
 *
 * This file contains functions responsible for various aspects of client handling,
 * including validating client names, managing connections and disconnections,
 * handling messages between clients, and processing client commands such as list,
 * connect, disconnect, and quit.
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

void ValidateName(Client_node_t *cli, char *buffer)
{
    char name[NAME_LEN];

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
}

void HandleConnect(Client_node_t *cli, char *buffer)
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

void HandleDisconnect(Client_node_t *cli)
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

void HandleQuit(Client_node_t *cli)
{
    char buffer[BUFFER_SIZE];

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
    memset(buffer, '\0', sizeof(buffer));
    snprintf(buffer, BUFFER_SIZE, "\n*** %s has left the chat ***\n", cli->name);
    printf("%s", buffer);
    pthread_mutex_unlock(&clients_mutex);
}

void SendReceivedMessage(Client_node_t *cli, char *buffer)
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

void *HandleClient(void *arg)
{
    char buffer[BUFFER_SIZE];
    int leave_flag = 0;
    Client_node_t *cli = (Client_node_t *)arg;

    ValidateName(cli, buffer);

    while (1)
    {
        if (leave_flag)
        {
            break;
        }

        memset(buffer, '\0', sizeof(buffer));
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
                HandleConnect(cli, buffer);
            }
            else if (strcmp(buffer, "disconnect") == 0)
            {
                HandleDisconnect(cli);
            }
            else if (strcmp(buffer, "quit") == 0)
            {
                HandleQuit(cli);
                leave_flag = 1;
            }
            else
            {
                SendReceivedMessage(cli, buffer);
            }
        }
        else if (receive == 0 || strcmp(buffer, "quit") == 0)
        {
            HandleQuit(cli);
            leave_flag = 1;
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
