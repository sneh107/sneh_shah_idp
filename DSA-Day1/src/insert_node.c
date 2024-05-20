#include "../inc/linked_list.h"

extern int flag;

int InsertAtStart(void *head1, int num)
{
    Node_t **head = (Node_t **)head1;
    head1 = NULL;
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    if (new_node == NULL)
    {
        printf("Memory Allocation Failed!");
        return FAILURE;
    }
    new_node->data = num;
    new_node->next = *head;
    *head = new_node;

    new_node = NULL;
    return SUCCESS;
}

int InsertAtEnd(void *head1, int num)
{
    Node_t **head = (Node_t **)head1;
    head1 = NULL;
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    if (new_node == NULL)
    {
        printf("Memory Allocation Failed!");
        return FAILURE;
    }

    new_node->data = num;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return SUCCESS;
    }
    Node_t *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node = NULL;
    return SUCCESS;
}

int InsertNode(void *head1, int num)
{
    int size = 0;
    Node_t **head = (Node_t **)head1;
    head1 = NULL;
    size = getListlSize(*head, &size);
    if (size >= MAX_ALLOWED)
    {
        printf("Maximum limit Reached...\nOperation Cancelled...\n");
        return FAILURE;
    }

    if (flag == 0)
    {
        InsertAtStart(head, num);
    }
    else
    {
        InsertAtEnd(head, num);
    }
    return SUCCESS;
}