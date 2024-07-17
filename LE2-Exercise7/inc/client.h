/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file client.h
 * @brief Header file for client-side operations in the chat application.
 *
 * This file declares the functions and definitions used by the client program.
 * It includes function declarations for printing a guide, handling user input,
 * and managing message sending and receiving between the client and server.
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

#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"

/// @brief Server IP address. Adjust this if your server IP is different.
#define SERVER_IP "127.0.0.1"

/**
 * @brief Prints a guide for available commands to the user.
 *
 * This function outputs a list of commands that the user can use in the chat application,
 * such as listing connected clients, connecting to a client, disconnecting from a client,
 * and quitting the application.
 */
void PrintGuide();

/**
 * @brief Removes the newline character from a string.
 *
 * This function iterates through a character array and replaces the first occurrence
 * of the newline character (`\n`) with a null terminator (`\0`). It is used to sanitize
 * user input from `fgets` which includes the newline character at the end.
 *
 * @param arr The character array from which to remove the newline character.
 * @param length The length of the character array.
 */
void RemoveNewLine(char *arr, int length);

/**
 * @brief Handles sending messages from the client to the server.
 *
 * This function is executed in a separate thread. It continuously reads user input,
 * sends the input to the server, and handles the "quit" command to exit the application.
 *
 * @param sock Pointer to the socket file descriptor connected to the server.
 * @return void* Always returns NULL. The function exits the thread upon completion.
 */
void *SendMessageHandler(void *sock);

/**
 * @brief Handles receiving messages from the server.
 *
 * This function is executed in a separate thread. It continuously listens for messages
 * from the server and prints them to the console. It handles special messages such as
 * server shutdown notifications.
 *
 * @param sock Pointer to the socket file descriptor connected to the server.
 * @return void* Always returns NULL. The function exits the thread upon completion.
 */
void *ReceiveMessageHandler(void *sock);

#endif // CLIENT_H
