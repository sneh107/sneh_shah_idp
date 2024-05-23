/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file binary_search_tree.h
 * @brief Header file containing declarations for binary search tree.
 *
 * This header file defines structures and function prototypes for
 * operations on a binary search tree. It provides functions to
 * insert nodes , display tree nodes using level-order, in-order,
 * pre-order and post-order traversal techniques,search node in tree.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * May/21/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#ifndef BST_H
#define BST_H

/*******************
 * Includes
 *******************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**************************************
 * Structures, Enumerations, Typedefs
 *************************************/

/**
 * @struct node
 * @brief Structure representing a node in the Binary Search Tree.
 */
typedef struct node
{
    int data;
    int frequency;
    struct node *left;
    struct node *right;
} Node_t;

/**
 * @struct queuenode
 * @brief Structure representing a node in the queue used for level-order traversal.
 */
typedef struct queuenode
{
    struct node *data;
    struct queuenode *next;
} QueueNode_t;

typedef enum
{
    SUCCESS = 0,
    FAILURE
} exitStatus_e;

/************************
 * Function Prototypes
 ************************/

/**
 * @brief Inserts a new node with the given data into the Binary Search Tree.
 *
 * @param root Pointer to the pointer to the root of the Binary Search Tree.
 * @param data Data to be inserted into the Binary Search Tree.
 * @return 1 if successful, 0 otherwise.
 */
int InsertInTree(Node_t **root, int data);

/**
 * @brief Enqueues a tree node into the queue.
 *
 * @param queue Pointer to the pointer to the queue.
 * @param data Pointer to the tree node to be enqueued.
 * @return 1 if successful, 0 otherwise.
 */
int EnQueue(QueueNode_t **queue, Node_t *data);

/**
 * @brief Dequeues a tree node from the queue.
 *
 * @param queue Pointer to the pointer to the queue.
 * @return 1 if successful, 0 otherwise.
 */
int DeQueue(QueueNode_t **queue);

/**
 * @brief Performs level-order traversal of the Binary Search Tree.
 *
 * @param root Pointer to the root of the Binary Search Tree.
 * @return 1 if successful, 0 otherwise.
 */
int LevelOrderTraversal(Node_t *root);

/**
 * @brief Performs pre-order traversal of the Binary Search Tree.
 *
 * @param root Pointer to the root of the Binary Search Tree.
 * @return 1 if successful, 0 otherwise.
 */
int PreOrder(Node_t *root);

/**
 * @brief Performs in-order traversal of the Binary Search Tree.
 *
 * @param root Pointer to the root of the Binary Search Tree.
 * @return 1 if successful, 0 otherwise.
 */
int InOrder(Node_t *root);

/**
 * @brief Performs post-order traversal of the Binary Search Tree.
 *
 * @param root Pointer to the root of the Binary Search Tree.
 * @return 1 if successful, 0 otherwise.
 */
int PostOrder(Node_t *root);

/**
 * @brief Searches for a target value in the Binary Search Tree.
 *
 * @param root Pointer to the root of the Binary Search Tree.
 * @param target Value to be searched for.
 * @return 1 if successful, 0 otherwise.
 */
int searchNode(Node_t *root, int target);

/**
 * @brief Deletes the Binary Search Tree and frees the memory.
 *
 * @param root Pointer to the root of the Binary Search Tree.
 * @return 1 if successful, 0 otherwise.
 */
int DeleteTree(Node_t *root);

#endif