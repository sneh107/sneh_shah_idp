/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file main.c
 * @brief Entry point of the program with circular doubly linked list operations.
 *
 * This file contains the main function, which serves as the entry
 * point of the program. It demonstrates various operations on a
 * circular doubly linked list, including insertion at the beginning,
 * end, and intermediate positions, deletion at the beginning, end,
 * and intermediate positions, searching for a node, displaying the
 * list contents, getting the size of the list, and deleting the entire list.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Apr/30/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include "../inc/linked_list.h"

/**
 * @brief Entry point of program
 *
 * @return return 0 on success otherwise 1
 */
int main()
{
    int num = 0, index = 0;
    int operation_count = 0;
    Node_t *head = NULL;
    InsertAtEnd(&head, 10);
    InsertAtEnd(&head, 40);
    InsertAtEnd(&head, 30);
    InsertAtEnd(&head, 40);
    InsertAtEnd(&head, 50);

    Displaylist(head);
    int silliness_count = 0, exit_flag = 0, size = 0;

    while (exit_flag != 1 && silliness_count < 3)
    {
        printf("\nWhich operation You want to perform:\n");
        printf("01. Insert at beginning\n02. Insert at end\n03. Insert at Intermediate\n04. Delete at Beginning\n05. Delete at End\n06. Delete at Intermediate\n07. Search Node\n08. Display List\n09. Get List Size\n10. Delete List\n11. Exit\n");
        printf("Enter Choice: ");
        scanf(" %d", &operation_count);

        switch (operation_count)
        {
        case 1:
            printf("Enter element to insert: ");
            scanf(" %d", &num);
            InsertAtStart(&head, num);
            break;

        case 2:
            printf("Enter element to insert: ");
            scanf(" %d", &num);
            InsertAtEnd(&head, num);
            break;

        case 3:
            printf("Enter element to insert: ");
            scanf(" %d", &num);
            printf("Enter index at which you want to insert: ");
            scanf(" %d", &index);
            InsertNodeat(&head, num, index);
            break;

        case 4:
            DeleteAtStart(&head);
            break;

        case 5:
            DeleteAtEnd(&head);
            break;

        case 6:
            printf("Enter index at which you want to delete: ");
            scanf(" %d", &index);
            DeleteNodeat(&head, index);
            break;

        case 7:
            printf("Enter data you want to find: ");
            scanf(" %d", &num);
            FindNode(head, num);
            break;

        case 8:
            Displaylist(head);
            break;

        case 9:
            size = getListlSize(head);
            printf("Size of Linked list is %d.\n", size);
            break;

        case 10:
            DeleteList(&head);
            break;

        case 11:
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

    if (head == NULL)
    {
        return SUCCESS;
    }

    DeleteList(&head);

    return SUCCESS;
}