#include "../inc/linked_list.h"

void SequentialSearch(Node_t *head, int target)
{
    int count = 1, found_flag = 0;
    while (head != NULL)
    {

        if (head->data == target)
        {
            found_flag = 1;
            printf("%d found at index %d\n", target, count);
            count++;
        }
        else
        {
            count++;
        }
        head = head->next;
    }
    if (found_flag == 0)
    {
        printf("%d not found!\n", target);
    }
}

int binarySearch(Node_t *head, int target)
{
    BubbleSort(head);
    printf("Sorted List: ");
    Displaylist(head);

    int index = 1;
    int len = 0;
    len = getListlSize(head, &len);

    Node_t *first = head;
    Node_t *last = NULL;
    while (first != last)
    {
        Node_t *mid = first;
        int count = 0;
        while (count < len / 2)
        {
            mid = mid->next;
            count++;
        }
        if (mid->data == target)
        {
            return index + count;
        }
        else if (mid->data < target)
        {
            first = mid->next;
            len = len - count - 1;
            index = index + count + 1;
        }
        else
        {
            last = mid;
            len = count;
        }
    }
    return -1;
}

int SearchData(void *head1, int data, int searching_method)
{
    Node_t *head = (Node_t *)head1;
    head1 = NULL;

    if (head == NULL)
    {
        printf("Empty List!\nOperation Cancelled...\n");
        return SUCCESS;
    }

    int found_index = 0;
    switch (searching_method)
    {
    case 0:
        SequentialSearch(head, data);
        break;

    case 1:
        found_index = binarySearch(head, data);
        if (found_index != -1)
        {
            printf("Element %d found at index %d in the sorted linked list.\n", data, found_index);
        }
        else
        {
            printf("Element %d not found in the linked list.\n", data);
        }
        break;

    default:
        printf("Invalid Input!\n");
        return FAILURE;
        break;
    }
    return SUCCESS;
}