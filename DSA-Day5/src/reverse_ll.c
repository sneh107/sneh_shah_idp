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