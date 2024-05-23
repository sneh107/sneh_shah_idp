#include "../inc/binary_search_tree.h"

int main()
{
    Node_t *root = NULL;
    clock_t start = 0, end = 0, time_required = 0;
    int data = 0;
    // 10 5 15 10 7 3
    // InsertInTree(&root, 10);
    // InsertInTree(&root, 5);
    // InsertInTree(&root, 15);
    // InsertInTree(&root, 10);
    // InsertInTree(&root, 7);
    // InsertInTree(&root, 3);
    printf("Enter tree elements (Ctrl+D to end):\n");
    while (scanf(" %d", &data) != EOF)
    {
        InsertInTree(&root, data);
        // while (getchar() != '\n')
        //     ;
    }
    // fflush(stdin);
    clearerr(stdin);
    // fflush(stdin);

    int operation_no = 0, silliness_count = 0, exit_flag = 0, traversal_method = 0;

    while (exit_flag != 1 && silliness_count < 3)
    {
        printf("\nSelect operation you want to perform:\n");
        printf("01. Insert node\n02. Traversal\n03. Search node\n04. Delete Tree\n05. Exit\n");
        printf("Enter Operation no. : ");

        scanf(" %d", &operation_no);

        switch (operation_no)
        {
        case 1:
            printf("Enter data to insert: ");
            scanf(" %d", &data);
            InsertInTree(&root, data);
            break;

        case 2:
            printf("Enter which sorting method you want to perform(0->Level-order|1->in-order|2->pre-order|3->post-order): ");
            scanf(" %d", &traversal_method);
            switch (traversal_method)
            {
            case 0:
                LevelOrderTraversal(root);
                break;
            case 1:
                start = clock();
                if (root == NULL)
                {
                    printf("Empty List!\nOperation Cancelled...\n");
                }
                else
                    InOrder(root);
                end = clock();
                time_required = end - start;
                printf("\nTime taken to traverse tree is %f seconds.\n",
                       (float)time_required / CLOCKS_PER_SEC);
                printf("\n");
                break;
            case 2:
                start = clock();
                if (root == NULL)
                {
                    printf("Empty List!\nOperation Cancelled...\n");
                }
                else
                    PreOrder(root);
                end = clock();
                time_required = end - start;
                printf("\nTime taken to traverse tree is %f seconds.\n",
                       (float)time_required / CLOCKS_PER_SEC);
                printf("\n");
                break;
            case 3:
                start = clock();
                if (root == NULL)
                {
                    printf("Empty List!\nOperation Cancelled...\n");
                }
                else
                    PostOrder(root);
                end = clock();
                time_required = end - start;
                printf("\nTime taken to traverse tree is %f seconds.\n",
                       (float)time_required / CLOCKS_PER_SEC);
                printf("\n");
                break;
            default:
                printf("Enter valid input!\n");
                break;
            }
            break;
        case 3:
            printf("Enter Element to search: ");
            scanf(" %d", &data);
            searchNode(root, data);
            break;
        case 4:
            if (root == NULL)
            {
                printf("Nothing to Delete!\nList is empty...\n");
            }
            else
            {
                DeleteTree(root);
                root = NULL;
            }
            break;
        case 5:
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
    if (root != NULL)
    {
        DeleteTree(root);
    }
    return 0;
}