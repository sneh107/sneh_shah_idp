/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file delete_ll.c
 * @brief Functions to delete nodes from a linked list.
 *
 * This file provides functions to delete nodes from a linked list
 * including deleting the first node, deleting a node from a
 * specified position, and deleting the entire linked list.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * May/02/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include "../inc/linked_list.h"

int DeleteNode(void *head1)
{
    Node_t **head = (Node_t **)head1;
    head1 = NULL;
    if (*head == NULL)
    {
        printf("Nothing to Delete!\nList is empty...\n");
        return SUCCESS;
    }

    Node_t *temp = *head;
    *head = (*head)->next;
    free(temp);
    temp = NULL;
    return SUCCESS;
}

int DeleteNodeFrom(void *head1, int node_position)
{
    Node_t **head = (Node_t **)head1;
    head1 = NULL;

    if (*head == NULL)
    {
        printf("Nothing to Delete!\nList is empty...\n");
        return SUCCESS;
    }

    if (node_position == 1)
    {
        DeleteNode(head);
        return SUCCESS;
    }

    int size = 0;
    size = getListlSize(*head, &size);
    if (node_position <= 0 || node_position > size)
    {
        printf("Invalid posiition!\n");
        return FAILURE;
    }

    int count = 1;
    Node_t *ptr = *head;
    while (count != (node_position - 1))
    {
        count++;
        ptr = ptr->next;
    }
    Node_t *temp = ptr->next;
    ptr->next = ptr->next->next;
    ptr = NULL;
    free(temp);
    temp = NULL;
    return SUCCESS;
}

int deletelist(void *head1)
{
    Node_t **head = (Node_t **)head1;
    head1 = NULL;
    if (*head == NULL)
    {
        printf("Nothing to Delete!\nList is empty...\n");
        return SUCCESS;
    }
    Node_t *temp = NULL;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        temp = NULL;
    }
    *head = NULL;
    return SUCCESS;
}