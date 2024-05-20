#include "../inc/linked_list.h"

int Displaylist(void *head1)
{
    Node_t *head = (Node_t *)head1;
    head1 = NULL;
    if (head == NULL)
    {
        printf("Empty!");
        return FAILURE;
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