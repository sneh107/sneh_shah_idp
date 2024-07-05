#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 7777
#define BUFFER_SIZE 1024
#define NAME_LEN 32
#define SERVER_IP "192.168.3.147"

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
            // if (strstr(buffer, "Name incorrect") != NULL)
            // {
            //     printf("Quiting...\n\n");
            //     // close(server_sock);
            //     exit(EXIT_FAILURE);
            // }

            // else if (strstr(buffer, "Name already taken") != NULL)
            // {
            //     printf("Quiting...\n\n");
            //     // close(server_sock);
            //     exit(EXIT_FAILURE);
            // }

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

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    char name[NAME_LEN];
    printf("Enter your name: ");
    fgets(name, NAME_LEN, stdin);
    RemoveNewLine(name, strlen(name));
    if (strlen(name) > 0)
    {
        send(sock, name, strlen(name), 0);
    }
    else
    {
        printf("Name cannot be empty\n");
        return -1;
    }

    PrintGuide();

    pthread_t send_msg_thread, recv_msg_thread;
    if (pthread_create(&send_msg_thread, NULL, SendMessageHandler, &sock) != 0)
    {
        printf("Failed to create send message thread\n");
        return -1;
    }
    if (pthread_create(&recv_msg_thread, NULL, ReceiveMessageHandler, &sock) != 0)
    {
        printf("Failed to create receive message thread\n");
        return -1;
    }

    pthread_join(send_msg_thread, NULL);
    pthread_join(recv_msg_thread, NULL);

    close(sock);

    return 0;
}
