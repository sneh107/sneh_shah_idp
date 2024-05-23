#include "../inc/binary_search_tree.h"

int InsertInTree(Node_t **root, int data)
{
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    if (new_node == NULL)
    {
        printf("Allocation Failed!\n");
        return FAILURE;
    }
    new_node->data = data;
    new_node->frequency = 1;
    new_node->left = NULL;
    new_node->right = NULL;

    if (*root == NULL)
    {
        *root = new_node;
        new_node = NULL;
        return SUCCESS;
    }

    Node_t *current = *root;
    Node_t *parent = NULL;
    while (current != NULL)
    {
        parent = current;
        if (data < current->data)
        {
            current = current->left;
        }
        else if (data > current->data)
        {
            current = current->right;
        }
        else if (data == current->data)
        {
            current->frequency++;
            break;
        }
    }
    if (data < parent->data)
    {
        parent->left = new_node;
    }
    else if (data > parent->data)
    {
        parent->right = new_node;
    }
    else
    {
        free(new_node);
        new_node = NULL;
    }
    parent = NULL;
    current = NULL;
    return SUCCESS;
}