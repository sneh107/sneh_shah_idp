#include "../inc/linked_list.h"
int InsertNode(void *head1, int num);

int Initlinklist(void **head, int max_size_of_queue, int flag)
{
    Node_t **head1 = (Node_t **)head;
    head = NULL;
    // Node_t *temp = NULL;
    int num = 0;
    for (int i = 0; i < max_size_of_queue; i++)
    {
        printf("Enter Element: ");
        scanf(" %d", &num);
        if (i == 0)
        {
            (*head1)->data = num;
            (*head1)->next = NULL;
        }
        else
        {
            InsertNode(head1, num);
        }
    }
    return SUCCESS;
}