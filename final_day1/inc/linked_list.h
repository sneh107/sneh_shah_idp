/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file linked_list.h
 * @brief Header file containing declarations for a singly linked list.
 *
 * This header file defines structures and function prototypes for
 * operations on a singly linked list. It provides functions to
 * insert nodes at the start, end, initialize the linked list,
 * and display its elements.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Apr/29/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*******************
 * Includes
 *******************/

#include <stdio.h>
#include <stdlib.h>

/*************************
 * Defines
 *************************/
#define MAX_ALLOWED 50

/**************************************
 * Structures, Enumerations, Typedefs
 *************************************/

/**
 * @brief Structure representing a node in the linked list.
 */
typedef struct node
{
    int data;
    struct node *next;
} Node_t;

typedef enum
{
    SUCCESS = 0,
    FAILURE
} exitStatus_e;

/************************
 * Function Prototypes
 ************************/

/**
 * @brief Inserts a new node with the given data at the start of the linked list.
 *
 * @param head1 Pointer to the pointer to the head of the linked list.
 * @param num The data to be inserted into the new node.
 * @return 1 if successful, 0 otherwise.
 */
int InsertAtStart(void *head1, int num);

/**
 * @brief Inserts a new node with the given data at the end of the linked list.
 *
 * @param head1 Pointer to the head of the linked list.
 * @param num The data to be inserted into the new node.
 * @return 1 if successful, 0 otherwise.
 */
int InsertAtEnd(void *head1, int num);

/**
 * @brief Inserts node based on stack or queue.
 *
 * @param head1 Pointer to the head of the linked list.
 * @param num The data to be inserted into the new node.
 * @return 1 if successful, 0 otherwise.
 */
int InsertNode(void *head1, int num);

/**
 * @brief Initializes the linked list with a maximum size and flag.
 *
 * @param head Pointer to the pointer to the head of the linked list.
 * @param max_size_of_queue Maximum size of the linked list.
 * @param flag Flag indicating queue or stack.
 * @return 1 if successful, 0 otherwise.
 */
int Initlinklist(void **head, int max_size_of_queue, int flag);

/**
 * @brief Displays the elements of the linked list.
 *
 * @param head1 Pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int Displaylist(void *head1);

/**
 * @brief Gets the size of the linked list.
 *
 * @param head1 Pointer to the head of the linked list.
 * @param length Pointer to an integer variable to store the size of the linked list.
 * @return size of linked list
 */
int getListlSize(void *head1, int *length);

/**
 * @brief Deletes all nodes from the linked list.
 *
 * @param head1 Pointer to the pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int deletelist(void *head1);

#endif