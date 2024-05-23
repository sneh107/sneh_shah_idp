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
