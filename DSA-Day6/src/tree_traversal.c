#include "../inc/binary_search_tree.h"

int EnQueue(QueueNode_t **queue, Node_t *data)
{
    QueueNode_t *new_node = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (new_node == NULL)
    {
        printf("Allocation Failed!\n");
        return FAILURE;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (*queue == NULL)
    {
        *queue = new_node;
        new_node = NULL;
        return SUCCESS;
    }

    QueueNode_t *temp = *queue;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
    temp = NULL;
    new_node = NULL;
    return SUCCESS;
}

int DeQueue(QueueNode_t **queue)
{
    if (*queue == NULL)
        return SUCCESS;

    QueueNode_t *temp = *queue;
    *queue = (*queue)->next;

    free(temp);
    temp = NULL;
    return SUCCESS;
}

int LevelOrderTraversal(Node_t *root)
{
    clock_t start = 0, end = 0, time_required = 0;
    if (root == NULL)
    {
        printf("Empty List!\nOperation Cancelled...\n");
        return SUCCESS;
    }
    QueueNode_t *queue = NULL;
    start = clock();
    EnQueue(&queue, root);
    while (queue != NULL)
    {
        int copy = queue->data->frequency;
        while (copy--)
        {
            printf("%d ", queue->data->data);
        }

        Node_t *temp = queue->data;
        DeQueue(&queue);

        if (temp->left != NULL)
        {
            EnQueue(&queue, temp->left);
        }
        if (temp->right != NULL)
        {
            EnQueue(&queue, temp->right);
        }
    }
    end = clock();
    time_required = end - start;
    printf("\nTime taken to traverse tree is %f seconds.\n", (float)time_required / CLOCKS_PER_SEC);
    return SUCCESS;
}

int PreOrder(Node_t *root)
{
    if (root == NULL)
    {
        return SUCCESS;
    }
    int copy = root->frequency;
    while (copy--)
    {
        printf("%d ", root->data);
    }

    PreOrder(root->left);
    PreOrder(root->right);
    return SUCCESS;
}

int InOrder(Node_t *root)
{
    if (root == NULL)
    {
        return SUCCESS;
    }

    InOrder(root->left);
    int copy = root->frequency;
    while (copy--)
    {
        printf("%d ", root->data);
    }
    InOrder(root->right);
    return SUCCESS;
}

int PostOrder(Node_t *root)
{
    if (root == NULL)
    {
        // printf("Tree is empty\n");
        return SUCCESS;
    }

    PostOrder(root->left);
    PostOrder(root->right);
    int copy = root->frequency;
    while (copy--)
    {
        printf("%d ", root->data);
    }
    return SUCCESS;
}