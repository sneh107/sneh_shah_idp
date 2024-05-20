#include "../inc/linked_list.h"

extern int flag;

int InsertAtStart(void *head1, int num, int priority)
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
    new_node->priority = priority;
    new_node->next = *head;
    *head = new_node;

    new_node = NULL;
    return SUCCESS;
}

int InsertAtEnd(void *head1, int num, int priority)
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
    new_node->priority = priority;
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
    temp = NULL;
    return SUCCESS;
}

int InsertNode(void *head1, int num, int priority)
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
        InsertAtStart(head, num, priority);
    }
    else
    {
        InsertAtEnd(head, num, priority);
    }
    return SUCCESS;
}

int InsertNodeat(void *head1, int data, int node_position, int priority)
{
    Node_t **head = (Node_t **)head1;
    head1 = NULL;

    int size = 0;
    size = getListlSize(*head, &size);

    if (size >= MAX_ALLOWED)
    {
        printf("Maximum limit Reached...\nOperation Cancelled...\n");
        return FAILURE;
    }

    if (node_position <= 0 || node_position > (size + 1))
    {
        printf("Invalid posiition!\n");
        if (size == 0)
        {
            printf("Current list is Empty!\n");
        }
        else
            printf("Current List Size is %d\n", size);
        return FAILURE;
    }

    if (node_position == 1)
    {
        InsertAtStart(head, data, priority);
        return SUCCESS;
    }

    Node_t *temp = (Node_t *)malloc(sizeof(Node_t));
    if (temp == NULL)
    {
        printf("Memory Allocation Failed!");
        return FAILURE;
    }

    temp->data = data;
    temp->priority = priority;

    int count = 1;
    Node_t *ptr = *head;
    while (count != (node_position - 1))
    {
        count++;
        ptr = ptr->next;
    }

    Node_t *temp1 = NULL;
    temp1 = ptr->next;
    ptr->next = temp;
    temp->next = temp1;

    temp1 = NULL;
    temp = NULL;
    ptr = NULL;
    return SUCCESS;
}