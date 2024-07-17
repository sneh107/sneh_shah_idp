/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file server.h
 * @brief Header file for server-side operations in the chat application.
 *
 * This file declares the functions and definitions used by the server program.
 * It includes function declarations for handling client connections, managing the client list,
 * and processing client commands.
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

#ifndef SERVER_H
#define SERVER_H

#include "common.h"

/**
 * @brief Represents a client node in the linked list.
 */
typedef struct Client_node
{
    int sock;                 /**< Socket descriptor for the client. */
    char name[NAME_LEN];      /**< Name of the client. */
    int connected_to;         /**< Socket descriptor of the client this client is connected to. */
    struct Client_node *next; /**< Pointer to the next client node in the list. */
} Client_node_t;

extern Client_node_t *clients_head;
extern pthread_mutex_t clients_mutex;
extern int server_running;
extern int server_fd;

/**
 * @brief Adds a client to the list of connected clients.
 *
 * This function appends a new client node to the beginning of the linked list of clients.
 *
 * @param client Pointer to the client node to add.
 */
void AddClient(Client_node_t *client);

/**
 * @brief Removes a client from the list of connected clients.
 *
 * This function removes the client node with the specified socket descriptor from the linked list of clients.
 *
 * @param sock The socket descriptor of the client to remove.
 */
void RemoveClient(int sock);

/**
 * @brief Frees all clients from the linked list.
 *
 * This function iterates through the linked list of clients, closes their sockets, and frees their memory.
 */
void FreeAllClients();

/**
 * @brief Sends a list of all connected clients to the specified socket.
 *
 * This function constructs a list of all connected clients' names and sends it to the specified client socket.
 *
 * @param sock The socket descriptor to send the list to.
 */
void ListClients(int sock);

/**
 * @brief Removes the newline character from a string.
 *
 * This function iterates through a character array and replaces the first occurrence of the newline character (`\n`)
 * with a null terminator (`\0`). It is used to sanitize user input from `fgets` which includes the newline character at the end.
 *
 * @param arr The character array from which to remove the newline character.
 * @param length The length of the character array.
 */
void RemoveNewLine(char *arr, int length);

/**
 * @brief Checks if a given name is unique among connected clients.
 *
 * This function iterates through the linked list of clients to check if the specified name is already taken by another client.
 *
 * @param name The name to check for uniqueness.
 * @return int Returns 1 if the name is unique, 0 otherwise.
 */
int IsNameUnique(char *name);

/**
 * @brief Broadcasts a shutdown message to all connected clients.
 *
 * This function sends a shutdown message to all connected clients and closes their sockets.
 */
void BroadcastShutdownMessage();

/**
 * @brief Signal handler for SIGINT.
 *
 * This function handles the SIGINT signal (generated by Ctrl+C) to shut down the server gracefully.
 *
 * @param sig The signal number.
 */
void SignalHandler(int sig);

/**
 * @brief Validates the name of a newly connected client.
 *
 * This function ensures that a client's name is unique and valid. It prompts the client to enter a unique name if necessary.
 *
 * @param cli Pointer to the client node.
 * @param buffer Buffer to store messages.
 */
void ValidateName(Client_node_t *cli, char *buffer);

/**
 * @brief Handles a client's request to connect to another client.
 *
 * This function processes the connect command from a client and connects them to the specified target client if possible.
 *
 * @param cli Pointer to the client node.
 * @param buffer Buffer containing the connect command.
 */
void HandleConnect(Client_node_t *cli, char *buffer);

/**
 * @brief Handles a client's request to disconnect from their current connection.
 *
 * This function processes the disconnect command from a client and disconnects them from their current connection if they are connected.
 *
 * @param cli Pointer to the client node.
 */
void HandleDisconnect(Client_node_t *cli);

/**
 * @brief Handles a client's request to quit the chat.
 *
 * This function processes the quit command from a client, disconnects them if they are connected, and removes them from the clients list.
 *
 * @param cli Pointer to the client node.
 */
void HandleQuit(Client_node_t *cli);

/**
 * @brief Sends a received message to the connected client.
 *
 * This function formats and sends a message from one client to the client they are connected to.
 *
 * @param cli Pointer to the client node.
 * @param buffer Buffer containing the message to send.
 */
void SendReceivedMessage(Client_node_t *cli, char *buffer);

/**
 * @brief Handles client communication.
 *
 * This function runs in a separate thread for each client. It handles receiving messages from the client,
 * processing commands, and forwarding messages to connected clients.
 *
 * @param arg Pointer to the client node.
 * @return void* Always returns NULL. The function exits the thread upon completion.
 */
void *HandleClient(void *arg);

#endif // SERVER_H
