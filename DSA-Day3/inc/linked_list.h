/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file linked_list.h
 * @brief Header file containing declarations for circular doubly linked list.
 *
 * This header file defines structures and function prototypes for
 * operations on a circular doubly linked list. It provides functions to
 * insert nodes at the start, end, intermediate,
 * display its elements, and perform various other operations
 * such as insertion, deletion, finding node, and getting the
 * size of the list.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Apr/30/2024, Sneh Shah, Created
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

/**
 * @brief Structure representing a node in the linked list.
 */
typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
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
 * @param head Pointer to the pointer to the head of the linked list.
 * @param num The data to be inserted into the new node.
 * @return 1 if successful, 0 otherwise.
 */
int InsertAtStart(Node_t **head, int num);

/**
 * @brief Inserts a new node with the given data at the end of the linked list.
 *
 * @param head Pointer to the pointer to the head of the linked list.
 * @param num The data to be inserted into the new node.
 * @return 1 if successful, 0 otherwise.
 */
int InsertAtEnd(Node_t **head, int num);

/**
 * @brief Inserts a new node with the given data at the specified position in the linked list.
 *
 * @param head Pointer to the head of the linked list.
 * @param num The data to be inserted into the new node.
 * @param index The position where the new node will be inserted.
 * @return 1 if successful, 0 otherwise.
 */
int InsertNodeat(Node_t **head, int num, int index);

/**
 * @brief Deletes the first node in the linked list.
 *
 * @param head Pointer to the pointer to the head of the linked list.
 */
int DeleteAtStart(Node_t **head);

/**
 * @brief Deletes the last node in the linked list.
 *
 * @param head Pointer to the head of the linked list.
 */
int DeleteAtEnd(Node_t **head);

/**
 * @brief Deletes a node at the specified index in the linked list.
 *
 * @param head Pointer to the head of the linked list.
 * @param index Index of the node to be deleted.
 */
int DeleteNodeat(Node_t **head, int index);

/**
 * @brief Finds the occurrences of a given data in thelinked list and prints its index.
 *
 * @param head Pointer to the head of the list.
 * @param num  Data to be found.
 */
int FindNode(Node_t *head, int num);

/**
 * @brief Displays the elements of the doubly linked list.
 *
 * @param head1 Pointer to the head of the list.
 * @return 1 if the list is empty, 0 otherwise.
 */
int Displaylist(void *head1);

/**
 * @brief Deletes all nodes from the linked list.
 *
 * @param head Pointer to the pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int DeleteList(Node_t **head);

/**
 * @brief Gets the size of the linked list.
 *
 * @param head Pointer to the head of the linked list.
 * @return size of linked list
 */
int getListlSize(Node_t *head);

#endif