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
 * display its elements, and perform various other operations
 * such as insertion, deletion, reversal, getting the
 * size of the list and sorting the list.
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
 * @param head1 Pointer to the pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int Displaylist(void *head1);

/**
 * @brief Inserts a new node with the given data at the specified position in the linked list.
 *
 * @param head1 Pointer to the head of the linked list.
 * @param data The data to be inserted into the new node.
 * @param node_position The position where the new node will be inserted.
 * @return 1 if successful, 0 otherwise.
 */
int InsertNodeat(void *head1, int data, int node_position);

/**
 * @brief Deletes the first node from the linked list.
 *
 * @param head1 Pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int DeleteNode(void *head1);

/**
 * @brief Deletes the node at the specified position from the linked list.
 *
 * @param head1 Pointer to the head of the linked list.
 * @param node_position The position of the node to be deleted.
 * @return 1 if successful, 0 otherwise.
 */
int DeleteNodeFrom(void *head1, int node_position);

/**
 * @brief Deletes all nodes from the linked list.
 *
 * @param head1 Pointer to the pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int deletelist(void *head1);

/**
 * @brief Reverses the order of nodes in the linked list.
 *
 * @param head1 Pointer to the pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int ReverseList(void *head1);

/**
 * @brief Gets the size of the linked list.
 *
 * @param head1 Pointer to the head of the linked list.
 * @param length Pointer to an integer variable to store the size of the linked list.
 * @return size of linked list
 */
int getListlSize(void *head1, int *length);

/**
 * @brief Main function to perform sorting as per the user requirement
 *
 * @param head1 Pointer to the head of the linked list.
 * @param sorting_method The method with which sorting will be performed
 * @return 1 if successful, 0 otherwise.
 */
int Sortlist(void *head1, int sorting_method);

/**
 * @brief function to decide the order of sorting whether ascending order or descending order for quick sort
 * @param *a pointer for first variable to be compared
 * @param *b pointer for second variable to be compared
 */
int Compare(const void *a, const void *b);

/**
 * @brief function to convert a list to an array
 *
 * @param *arr the pointer to the array.
 * @param head Pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int ListToArr(int *arr, Node_t *head);

/**
 * @brief function to convert a array to an list
 *
 * @param *arr the pointer to the array.
 * @param head Pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int ArrToList(int *arr, Node_t *head);

/**
 * @brief Function to perform Bubble Sort
 *
 * @param head Pointer to the head of the linked list.
 */
void BubbleSort(Node_t *head);

/**
 * @brief Function to perform Quick Sort
 *
 * @param head Pointer to the head of the linked list.
 * @return 1 if successful, 0 otherwise.
 */
int QuickSort(Node_t *head);

/**
 * @brief Function to delete the last node
 *
 * @param ptr head of the list
 */
void DeleteLast(Node_t *ptr);

/**
 * @brief Function to find the maximum value in the link list
 *
 * @param head head of the link list
 * @return maximum value
 */
int FindMax(Node_t *head);

/**
 *
 * @brief Function to create a duplicate of the list
 *
 * @param head the head of the list
 * @return head of copy list
 */
Node_t *copyList(Node_t *head);

/**
 * @brief Funcion to perform counting sort for radix sort
 *
 * @param head the head of the list
 * @param pos the place at which counting sort will be performed
 * @return updated head pointer according to count sort wrt its place
 */
Node_t *CountingSort(Node_t *head, int pos);

/**
 * @brief The function to search data with different searching methods
 *
 * @param head the head of the list
 * @param data The data to be searched from the link list.
 * @param searching_method To select between the sorting methods.
 * @return 1 if successful, 0 otherwise.
 */
int SearchData(void *head1, int data, int searching_method);

/**
 * @brief The function to do binary search on a link list.
 *
 * @param head the head of the list
 * @param target The data to be searched in the link list.
 * @return index of data to be searched, -1 if not found
 */
int binarySearch(Node_t *head, int target);

/**
 * @brief This function does the linear searching for the link list
 *
 * @param head This is the head of the link list
 * @param target the data to be searched from the link list.
 */
void SequentialSearch(Node_t *head, int target);

#endif