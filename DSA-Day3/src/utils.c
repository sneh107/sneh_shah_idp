#include "../inc/linked_list.h"

int DeleteList(Node_t **head)
{
    if (*head == NULL)
    {
        printf("Nothing to Delete!\nList is empty...\n");
        return SUCCESS;
    }

    Node_t *ptr = *head;
    Node_t *temp = NULL;
    do
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
        temp = NULL;
    } while (ptr != *head);
    ptr = NULL;
    *head = NULL;
    return SUCCESS;
}

int getListlSize(Node_t *head)
{
    Node_t *temp = head;
    int count = 0;
    if (head == NULL)
    {
        return count;
    }
    do
    {
        count++;
        temp = temp->next;
    } while (temp != head);
    temp = NULL;
    head = NULL;
    return count;
}

int FindNode(Node_t *head, int num)
{
    if (head == NULL)
    {
        printf("Empty List!\nOperation Cancelled...\n");
        return SUCCESS;
    }
    int count = 1, flag = 0;
    Node_t *ptr = head;
    do
    {
        if (num == ptr->data)
        {
            flag = 1;
            printf("%d found at index %d\n", num, count);
            count++;
        }
        else
        {
            count++;
        }
        ptr = ptr->next;

    } while (ptr != head);
    ptr = NULL;
    head = NULL;
    if (flag == 0)
    {
        printf("%d not found!\n", num);
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
    Node_t *temp = head;
    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    temp = NULL;
    head = NULL;
    printf("\n");
    return SUCCESS;
}