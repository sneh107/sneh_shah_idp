/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file reverse_ll.c
 * @brief Functions to reverse a linked list.
 *
 * This file contains functions to reverse a linked list using
 * iterative and recursive approaches.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Apr/29/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include "../inc/linked_list.h"

// int ReverseList(void *head1)
// {
//     Node_t **head = (Node_t **)head1;
//     Node_t *prev = NULL;
//     Node_t *next = NULL;
//     while (*head != NULL)
//     {
//         next = (*head)->next;
//         (*head)->next = prev;
//         prev = *head;
//         *head = next;
//     }
//     *head = prev;
//     return SUCCESS;
// }

Node_t *reverseLinkedListRecursive(Node_t *head, Node_t *prev)
{
    if (head == NULL)
    {
        return prev;
    }

    Node_t *next = head->next;
    head->next = prev;
    return reverseLinkedListRecursive(next, head);
}

int ReverseList(void *head1)
{
    Node_t **head = (Node_t **)head1;
    head1 = NULL;

    if (*head == NULL)
    {
        printf("Empty List!\nOperation Cancelled...\n");
        return SUCCESS;
    }

    *head = reverseLinkedListRecursive(*head, NULL);

    return SUCCESS;
}