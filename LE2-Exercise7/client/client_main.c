/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file client_main.c
 * @brief Main file for the chat client application.
 *
 * This file contains the main function that initializes the client socket,
 * connects to the server, handles user input for the client's name, and
 * spawns threads for sending and receiving messages.
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

#include "../inc/client.h"

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
