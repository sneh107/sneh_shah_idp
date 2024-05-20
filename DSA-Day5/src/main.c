#include "../inc/linked_list.h"

// 75 4 802 3 45 1 90 5 170 2
// 1 75 2 802 3 45 4 90 5 170

int flag = 0;

void DisplaylistPriority(Node_t *head)
{
    printf("Data\tPriority\n");
    while (head != NULL)
    {
        printf("%d\t%d\n", head->data, head->priority);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    int max_size = 0, length = 0, sorting_method = 0, searching_method = 0;
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

    Node_t *head = (Node_t *)malloc(sizeof(Node_t));
    if (head == NULL)
    {
        printf("Memory Allocatio Failed!");
        return FAILURE;
    }
    Initlinklist((void **)&head, max_size, flag);

    Displaylist(head);

    int operation_no = 0, silliness_count = 0, exit_flag = 0;

    while (exit_flag != 1 && silliness_count < 3)
    {
        printf("\nSelect operation you want to perform:\n");
        printf("01. Insert node at index\n02. Delete Node\n03. Delete node from\n04. Delete List\n05. Reverse List\n06. get list size\n07. Insert Node\n08. Display List\n09. Display list with priority\n10. Sort List Based on data\n11. Sort list based on priority\n12. Search Data\n13. Exit\n");
        printf("Enter Operation no. : ");

        scanf(" %d", &operation_no);

        int data = 0, node_position = 0, priority = 0;
        switch (operation_no)
        {
        case 1:
            printf("Enter data to insert: ");
            scanf(" %d", &data);
            printf("Enter index at which you want data: ");
            scanf(" %d", &node_position);
            printf("Enter priority of %d: ", data);
            scanf(" %d", &priority);
            InsertNodeat(&head, data, node_position, priority);
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
            printf("Enter priority of %d: ", data);
            scanf(" %d", &priority);
            InsertNode(&head, data, priority);
            break;

        case 8:
            Displaylist(head);
            break;

        case 9:
            DisplaylistPriority(head);
            break;

        case 10:
            printf("Enter which sorting method you want to perform(0-bubble|1-radix|2-quick): ");
            scanf(" %d", &sorting_method);
            Sortlist(&head, sorting_method);
            break;

        case 11:
            printf("Enter which sorting method you want to perform(0-bubble|1-radix): ");
            scanf(" %d", &sorting_method);
            SortlistPriority(&head, sorting_method);
            break;

        case 12:
            printf("Enter data to search: ");
            scanf(" %d", &data);

            printf("Enter which searching method you want to use(0:Sequential search | 1:Binary search): ");
            scanf(" %d", &searching_method);
            SearchData(head, data, searching_method);
            break;

        case 13:
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