/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file search_node.c
 * @brief File containing function for searching a node in a binary search tree.
 *
 * This file implements the searchNode function, which searches
 * for a node with a given target value in a binary search tree.
 * It returns the frequency of occurrence of the target value if
 * found, otherwise it prints a message indicating that the value
 * was not found.
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

int searchNode(Node_t *root, int target)
{
    if (root == NULL)
    {
        printf("Empty List!\nOperation Cancelled...\n");
        return SUCCESS;
    }

    clock_t start = 0, end = 0, time_required = 0;
    start = clock();
    Node_t *current = root;

    while (current != NULL && current->data != target)
    {
        if (target < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (current == NULL)
    {
        printf("%d not found!\n", target);
    }
    else
    {
        printf("%d found with frequency of %d\n", target, current->frequency);
        current = NULL;
    }
    end = clock();
    time_required = end - start;
    printf("Time taken to search node in tree is %f seconds.\n", (float)time_required / CLOCKS_PER_SEC);
    return SUCCESS;
}
