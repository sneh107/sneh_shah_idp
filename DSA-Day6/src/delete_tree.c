/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file delete_tree.c
 * @brief File containing function to delete a binary search tree.
 *
 * This file implements a function to delete a binary search tree.
 * It recursively deletes each node of the tree, starting from the
 * leaves and moving towards the root.
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

#include "../inc/binary_search_tree.h"

int DeleteTree(Node_t *root)
{
    if (root == NULL)
    {
        return SUCCESS;
    }
    DeleteTree(root->left);
    DeleteTree(root->right);
    free(root);
    root = NULL;
    return SUCCESS;
}