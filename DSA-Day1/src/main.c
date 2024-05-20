#include "../inc/linked_list.h"

int flag = 0;

/**
 * @brief Entry point of program
 *
 * @return return 0 on success otherwise 1
 */
int main()
{
    int max_size = 0;
    Node_t *head = NULL;
    // Node_t *ptr = NULL;

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

    int operation_no = 0, num = 0, silliness_count = 0, exit_flag = 0;
    while (exit_flag != 1 && silliness_count < 3)
    {
        printf("Select operation you want to perform:\n");
        printf("1. Insert node\n2. Display List\n3. Exit\n");
        printf("Enter Operation no. : ");

        scanf(" %d", &operation_no);

        switch (operation_no)
        {
        case 1:
            printf("Enter Element: ");
            scanf(" %d", &num);
            InsertNode(&head, num);
            break;

        case 2:
            Displaylist(head);
            break;

        case 3:
            printf("Exiting...\n");
            exit_flag = 1;
            // exit(0);
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

    return SUCCESS;
}