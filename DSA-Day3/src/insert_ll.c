#include "../inc/linked_list.h"

int InsertAtStart(Node_t **head, int num)
{
    int size = getListlSize(*head);
    if (size >= MAX_ALLOWED)
    {
        printf("Maximum limit Reached...\nOperation Cancelled...\n");
        return FAILURE;
    }
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    if (new_node == NULL)
    {
        printf("Allocation Failed!\n");
        return FAILURE;
    }
    new_node->data = num;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL)
    {
        new_node->next = new_node;
        new_node->prev = new_node;
        *head = new_node;
        new_node = NULL;
        return SUCCESS;
    }

    Node_t *tail = NULL;
    tail = (*head)->prev;
    new_node->next = *head;
    new_node->prev = tail;
    tail->next = new_node;
    (*head)->prev = new_node;

    *head = new_node;
    tail = NULL;
    new_node = NULL;
    return SUCCESS;
}

int InsertAtEnd(Node_t **head, int num)
{
    int size = getListlSize(*head);
    if (size >= MAX_ALLOWED)
    {
        printf("Maximum limit Reached...\nOperation Cancelled...\n");
        return FAILURE;
    }
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    if (new_node == NULL)
    {
        printf("Allocation Failed!\n");
        return FAILURE;
    }
    new_node->data = num;
    new_node->next = NULL;
    new_node->prev = NULL;
    Node_t *tail = NULL;

    if (*head == NULL)
    {
        new_node->next = new_node;
        new_node->prev = new_node;
        *head = new_node;
        new_node = NULL;
        return SUCCESS;
    }

    tail = (*head)->prev;
    tail->next = new_node;
    new_node->prev = tail;
    new_node->next = *head;
    (*head)->prev = new_node;
    tail = NULL;
    new_node = NULL;

    return SUCCESS;
}

int InsertNodeat(Node_t **head, int num, int index)
{
    int size = getListlSize(*head);
    if (size >= MAX_ALLOWED)
    {
        printf("Maximum limit Reached...\nOperation Cancelled...\n");
        return FAILURE;
    }

    if (index <= 0 || index > (size + 1))
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
    if (index == 1)
    {
        InsertAtStart(head, num);
        return SUCCESS;
    }

    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    if (new_node == NULL)
    {
        printf("Allocation Failed!\n");
        return FAILURE;
    }
    new_node->data = num;
    new_node->next = NULL;
    new_node->prev = NULL;
    int count = 1;

    Node_t *ptr = *head;
    while (count != (index - 1))
    {
        count++;
        ptr = ptr->next;
    }
    Node_t *temp = NULL;
    temp = ptr->next;

    ptr->next = new_node;
    new_node->prev = ptr;
    new_node->next = temp;
    temp->prev = new_node;

    new_node = NULL;
    temp = NULL;
    ptr = NULL;
    return SUCCESS;
}