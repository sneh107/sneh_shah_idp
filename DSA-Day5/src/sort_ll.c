/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file sort_ll.c
 * @brief Functions for sorting elements in a linked list.
 *
 * This file provides functions for sorting elements in a linked list using different sorting algorithms,
 * such as bubble sort, radix sort, and quick sort.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * May/14/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include "../inc/linked_list.h"
#include <time.h>

int FindMaxPriority(Node_t *head)
{
    int max = head->priority;
    while (head != NULL)
    {
        if (head->priority > max)
        {
            max = head->priority;
        }
        head = head->next;
    }
    head = NULL;
    return max;
}

Node_t *CountingSortPriority(Node_t *head, int pos)
{
    Node_t *ptr = head;
    int count[10] = {0};

    while (ptr != NULL)
    {
        count[(ptr->priority / pos) % 10]++;
        ptr = ptr->next;
    }
    ptr = NULL;

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    Node_t *sorted = copyList(head);
    Node_t *head_ref = head;
    Node_t *tail_prev = NULL;
    Node_t *tail = NULL;
    int size = 0;
    size = getListlSize(sorted, &size);
    while (size != 0)
    {
        head_ref = head;
        if (head_ref->next == NULL)
        {
            ptr = head_ref;
            int digit = ((ptr->priority) / pos) % 10;
            int position_list = count[digit] - 1;

            Node_t *temp = sorted;
            while (position_list--)
            {
                temp = temp->next;
            }

            temp->data = ptr->data;
            temp->priority = ptr->priority;
            count[digit]--;
            size--;
            temp = NULL;

            return sorted;
        }

        while (head_ref->next->next != NULL)
        {
            head_ref = head_ref->next;
        }
        tail_prev = head_ref;
        tail = head_ref->next;
        ptr = tail;
        head_ref = head;
        int digit = ((ptr->priority) / pos) % 10;
        int position_list = count[digit] - 1;

        Node_t *temp = sorted;
        while (position_list--)
        {
            temp = temp->next;
        }

        temp->data = ptr->data;
        temp->priority = ptr->priority;
        ptr = tail_prev;
        count[digit]--;
        DeleteLast(head_ref);
        size--;
        tail = NULL;
        tail_prev = NULL;
        head_ref = NULL;
    }
    head = NULL;

    return sorted;
}

void RadixSortPriority(Node_t **head)
{
    Node_t *ptr = *head;
    // Node_t *ptr1;
    int max = FindMaxPriority(ptr);

    for (int pos = 1; max / pos > 0; pos *= 10)
    {
        ptr = CountingSortPriority(ptr, pos);
        *head = ptr;
    }
    ptr = NULL;
}

void BubbleSortPriority(Node_t *head)
{
    Node_t *current = head;
    head = NULL;

    while (current != NULL)
    {
        Node_t *nex = current->next;

        while (nex != NULL)
        {
            if (current->priority > nex->priority)
            {
                int temp = current->data;
                current->data = nex->data;
                nex->data = temp;

                temp = current->priority;
                current->priority = nex->priority;
                nex->priority = temp;
            }
            nex = nex->next;
        }
        current = current->next;
    }
    current = NULL;
}

int SortlistPriority(void *head1, int sorting_method)
{
    clock_t start = 0, end = 0, time_required = 0;
    Node_t **head = (Node_t **)head1;
    head1 = NULL;
    if (*head == NULL)
    {
        printf("Empty List!\nOperation Cancelled...\n");
        return SUCCESS;
    }
    start = clock();

    switch (sorting_method)
    {
    case 0:
        BubbleSortPriority(*head);
        end = clock();
        break;

    case 1:
        RadixSortPriority(head);
        end = clock();
        break;

    default:
        printf("Invalid Input!\n");
        break;
    }
    time_required = end - start;
    printf("Time taken to sort the list is %f seconds.\n", (float)time_required / CLOCKS_PER_SEC);
    return SUCCESS;
}

int Compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int ListToArr(int *arr, Node_t *head)
{
    Node_t *ptr = head;
    head = NULL;
    int i = 0;
    while (ptr != NULL)
    {
        arr[i] = ptr->data;
        ptr = ptr->next;
        i++;
    }
    ptr = NULL;
    return SUCCESS;
}

int ArrToList(int *arr, Node_t *head)
{
    Node_t *ptr = head;
    head = NULL;
    int i = 0;
    while (ptr != NULL)
    {
        ptr->data = arr[i];
        ptr = ptr->next;
        i++;
    }
    ptr = NULL;
    return SUCCESS;
}

void BubbleSort(Node_t *head)
{
    Node_t *current = head;
    head = NULL;

    while (current != NULL)
    {
        Node_t *nex = current->next;

        while (nex != NULL)
        {
            if (current->data > nex->data)
            {
                int temp = current->data;
                current->data = nex->data;
                nex->data = temp;

                temp = current->priority;
                current->priority = nex->priority;
                nex->priority = temp;
            }
            nex = nex->next;
        }
        current = current->next;
    }
    current = NULL;
}

int QuickSort(Node_t *head)
{
    int size = 0;
    size = getListlSize(head, &size);
    int arr[size];

    ListToArr(arr, head);
    qsort(arr, size, sizeof(int), Compare);
    ArrToList(arr, head);
    return SUCCESS;
}

void DeleteLast(Node_t *ptr)
{
    while (ptr->next->next != NULL)
    {
        ptr = ptr->next;
    }
    Node_t *temp;
    temp = ptr->next;
    ptr->next = NULL;
    free(temp);
    temp = NULL;
    ptr = NULL;
}

int FindMax(Node_t *head)
{
    int max = head->data;
    while (head != NULL)
    {
        if (head->data > max)
        {
            max = head->data;
        }
        head = head->next;
    }
    head = NULL;
    return max;
}

Node_t *copyList(Node_t *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {

        Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));

        newNode->data = head->data;
        newNode->priority = head->priority;
        newNode->next = copyList(head->next);
        head = NULL;

        return newNode;
    }
}

Node_t *CountingSort(Node_t *head, int pos)
{
    Node_t *ptr = head;
    int count[10] = {0};

    while (ptr != NULL)
    {
        count[(ptr->data / pos) % 10]++;
        ptr = ptr->next;
    }
    ptr = NULL;

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    Node_t *sorted = copyList(head);
    Node_t *head_ref = head;
    Node_t *tail_prev = NULL;
    Node_t *tail = NULL;
    int size = 0;
    size = getListlSize(sorted, &size);
    while (size != 0)
    {
        head_ref = head;
        if (head_ref->next == NULL)
        {
            ptr = head_ref;
            int digit = ((ptr->data) / pos) % 10;
            int position_list = count[digit] - 1;

            Node_t *temp = sorted;
            while (position_list--)
            {
                temp = temp->next;
            }

            temp->data = ptr->data;
            temp->priority = ptr->priority;
            count[digit]--;
            size--;
            temp = NULL;

            return sorted;
        }

        while (head_ref->next->next != NULL)
        {
            head_ref = head_ref->next;
        }
        tail_prev = head_ref;
        tail = head_ref->next;
        ptr = tail;
        head_ref = head;
        int digit = ((ptr->data) / pos) % 10;
        int position_list = count[digit] - 1;

        Node_t *temp = sorted;
        while (position_list--)
        {
            temp = temp->next;
        }

        temp->data = ptr->data;
        temp->priority = ptr->priority;
        ptr = tail_prev;
        count[digit]--;
        DeleteLast(head_ref);
        size--;
        tail = NULL;
        tail_prev = NULL;
        head_ref = NULL;
    }
    head = NULL;

    return sorted;
}

void RadixSort(Node_t **head)
{
    Node_t *ptr = *head;
    // Node_t *ptr1;
    int max = FindMax(ptr);

    for (int pos = 1; max / pos > 0; pos *= 10)
    {
        ptr = CountingSort(ptr, pos);
        *head = ptr;
    }
    ptr = NULL;
}

int Sortlist(void *head1, int sorting_method)
{
    clock_t start = 0, end = 0, time_required = 0;
    Node_t **head = (Node_t **)head1;
    head1 = NULL;
    if (*head == NULL)
    {
        printf("Empty List!\nOperation Cancelled...\n");
        return SUCCESS;
    }

    start = clock();
    switch (sorting_method)
    {
    case 0:
        BubbleSort(*head);
        break;

    case 1:
        RadixSort(head);
        break;

    case 2:
        QuickSort(*head);
        break;

    default:
        printf("Invalid Input!\n");
        break;
    }
    time_required = end - start;
    printf("Time taken to sort the list is %f seconds.\n", (float)time_required / CLOCKS_PER_SEC);
    return SUCCESS;
}