/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file utils.c
 * @brief Utility functions for linked list operations.
 *
 * This file contains utility functions to initialize a linked list,
 * display its contents, and get its size.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * May/14/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include "../inc/linked_list.h"

int Initlinklist(void **head, int max_size_of_queue, int flag)
{
    Node_t **head1 = (Node_t **)head;
    head = NULL;
    // Node_t *temp = NULL;
    int num = 0, priority = 0;
    for (int i = 0; i < max_size_of_queue; i++)
    {
        printf("Enter Element: ");
        scanf(" %d", &num);
        printf("Enter Priority of %d: ", num);
        scanf(" %d", &priority);

        if (i == 0)
        {
            (*head1)->data = num;
            (*head1)->priority = priority;
            (*head1)->next = NULL;
        }
        else
        {
            InsertNode(head1, num, priority);
        }
    }
    return SUCCESS;
}

int Displaylist(void *head1)
{
    Node_t *head = (Node_t *)head1;
    head1 = NULL;
    if (head == NULL)
    {
        printf("Empty!\n");
        return SUCCESS;
    }

    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
    head = NULL;
    return SUCCESS;
}

int getListlSize(void *head1, int *length)
{
    Node_t *head = (Node_t *)head1;
    if (head == NULL)
    {
        // (*length)++;
        return *length;
    }
    else
    {
        (*length)++;
        return getListlSize(head->next, length);
    }
}