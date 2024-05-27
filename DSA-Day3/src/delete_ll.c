/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file delete_ll.c
 * @brief Functions for deleting nodes from a circular doubly linked list.
 *
 * This file contains functions to delete nodes from a circular doubly linked list. The functions include deleting a node
 * at the beginning, end, or an intermediate position of the list.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Apr/30/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include "../inc/linked_list.h"

int DeleteAtStart(Node_t **head)
{
    if (*head == NULL)
    {
        printf("Nothing to Delete!\nList is empty...\n");
        return SUCCESS;
    }
    if ((*head)->next == *head)
    {
        free(*head);
        *head = NULL;
        head = NULL;
        return SUCCESS;
    }

    Node_t *tail = NULL, *temp = NULL;
    tail = (*head)->prev;
    temp = *head;
    *head = (*head)->next;
    (*head)->prev = tail;
    tail->next = *head;
    free(temp);
    temp = NULL;
    tail = NULL;
    return SUCCESS;
}

int DeleteAtEnd(Node_t **head)
{
    if (*head == NULL)
    {
        printf("Nothing to Delete!\nList is empty...\n");
        return SUCCESS;
    }
    if ((*head)->next == *head)
    {
        free(*head);
        *head = NULL;
        head = NULL;
        return SUCCESS;
    }

    Node_t *temp = (*head)->prev;
    Node_t *tail = (*head)->prev->prev;
    tail->next = *head;
    (*head)->prev = tail;
    free(temp);
    temp = NULL;
    tail = NULL;
    return SUCCESS;
}

int DeleteNodeat(Node_t **head, int index)
{
    if (*head == NULL)
    {
        printf("Nothing to Delete!\nList is empty...\n");
        return SUCCESS;
    }

    if (index == 1)
    {
        DeleteAtStart(head);
        return SUCCESS;
    }

    int size = getListlSize(*head);
    if (index <= 0 || index > size)
    {
        printf("Invalid posiition!\n");

        printf("Current List Size is %d\n", size);

        return FAILURE;
    }

    int count = 1;
    Node_t *temp = *head;
    while (count != index)
    {
        count++;
        temp = temp->next;
    }
    Node_t *previous = temp->prev;
    Node_t *nex = temp->next;
    previous->next = nex;
    nex->prev = previous;
    free(temp);
    temp = NULL;
    previous = NULL;
    nex = NULL;
    return SUCCESS;
}