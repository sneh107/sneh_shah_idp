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