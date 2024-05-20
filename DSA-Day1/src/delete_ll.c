#include "../inc/linked_list.h"

int deletelist(void *head1)
{
    Node_t **head = (Node_t **)head1;
    head1 = NULL;
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