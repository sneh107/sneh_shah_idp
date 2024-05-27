/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file main.c
 * @brief Main program for managing a linked list data structure.
 *
 * Implements a program to manage a linked list data structure. Allows the user
 * to choose between stack or queue operations, specify the maximum size of the list,
 * and perform various operations such as insertion, deletion, reversal, sorting, and display.
 * Also includes options to get the size of the list and exit the program.
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

// 75 802 45 170 90

int flag = 0;

int main()
{
    int max_size = 0, length = 0, sorting_method = 0;
    Node_t *head = NULL;
    // Node_t *ptr;

    printf("For Which you want to perform operations\n(0:stack|1:queue): ");
    scanf(" %d", &flag);
    if (flag != 0 && flag != 1)
    {
        printf("Invalid Type\n");
        return FAILURE;
    }

    printf("Enter how many Elements you want to enter in queue or stack: ");
    scanf(" %d", &max_size);

    if (max_size > MAX_ALLOWED)
    {
        printf("Beyond MAX limit!\n");
        return FAILURE;
    }

    if (max_size == 0)
    {
        head = NULL;
    }
    else
    {
        head = (Node_t *)malloc(sizeof(Node_t));
        if (head == NULL)
        {
            printf("Memory Allocatio Failed!");
            return FAILURE;
        }
    }
    Initlinklist((void **)&head, max_size, flag);

    Displaylist(head);

    int operation_no = 0, silliness_count = 0, exit_flag = 0;

    while (exit_flag != 1 && silliness_count < 3)
    {
        printf("\nSelect operation you want to perform:\n");
        printf("01. Insert node at index\n02. Delete Node\n03. Delete node from\n04. Delete List\n05. Reverse List\n06. get list size\n07. Insert Node\n08. Display List\n09. Sort List\n10. Exit\n");
        printf("Enter Operation no. : ");

        scanf(" %d", &operation_no);

        int data = 0, node_position = 0;
        switch (operation_no)
        {
        case 1:
            printf("Enter data to insert: ");
            scanf(" %d", &data);
            printf("Enter index at which you want data: ");
            scanf(" %d", &node_position);
            InsertNodeat(&head, data, node_position);
            break;

        case 2:
            DeleteNode(&head);
            break;

        case 3:
            printf("Enter index at which you want delete: ");
            scanf(" %d", &node_position);
            DeleteNodeFrom(&head, node_position);
            break;

        case 4:
            deletelist(&head);
            break;

        case 5:
            ReverseList(&head);
            break;

        case 6:
            printf("Size of Linked List is: %d\n", getListlSize(head, &length));
            break;

        case 7:
            printf("Enter Element: ");
            scanf(" %d", &data);
            InsertNode(&head, data);
            break;

        case 8:
            Displaylist(head);
            break;

        case 9:
            printf("Enter which sorting method you want to perform(0-bubble|1-radix|2-quick): ");
            scanf(" %d", &sorting_method);
            Sortlist(&head, sorting_method);
            break;

        case 10:
            printf("Exiting...\n");
            exit_flag = 1;
            break;

        default:
            printf("Enter valid Input!\n");
            silliness_count++;
            if (silliness_count == 3)
            {
                printf("Too many attempts!\nExiting Application...\n");
            }

            break;
        }
    }

    deletelist(&head);
    head = NULL;

    return SUCCESS;
}