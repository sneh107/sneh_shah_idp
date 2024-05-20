#include "../inc/linked_list.h"

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