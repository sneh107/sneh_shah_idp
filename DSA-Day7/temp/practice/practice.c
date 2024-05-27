#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

enum DisplayFlag
{
    new,
    refurbished,
    outdated,
    mostPurchased,
    outOfStock
};

typedef struct Mobilenode
{
    // int id;
    char name[50];
    char brandName[50];
    float price;
    // float discount;
    // float finalPrice;
    // enum DisplayFlag displayFlag;
    int quantity;
    // int count;

    // struct
    // {
    //     int ram;
    //     int storage;
    //     char chipset[50];
    //     int camera;
    // } config;
    // struct Mobilenode *prev;
    // struct Mobilenode *next;

} Mobile_t;

typedef struct ListNode
{
    Mobile_t data;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode_t;
ListNode_t *head = NULL;
// Mobile_t *head = NULL;

typedef enum
{
    FAILURE = -1,
    SUCCESS
} exitStatus_e;
int Displaylist(ListNode_t *head);
void AddMobile(ListNode_t **head);

void PrintAsterisk(int terminalWidth)
{
    for (int i = 0; i < terminalWidth; i++)
    {
        printf("\e[32m*\e[m");
    }
    printf("\n");
}

void PrintLeftPadding(int terminalWidth, int strLen)
{
    int padding = (terminalWidth - strLen) / 2;
    for (int i = 0; i < padding; i++)
    {
        printf(" ");
    }
}

void Escape()
{
    printf("\nPress \e[1;33mEnter\e[m to continue...\n");
    getchar();
    getchar();
}

void GetIntInput(int *num)
{
    while (scanf(" %d", num) != 1)
    {
        printf("Invalid input. Enter a number: ");
        // Clear the input buffer
        while (getchar() != '\n')
            ;
    }
}

void InitDisplay()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); /**< Get terminal window size */

    int terminalWidth = w.ws_col; /**< Width of the terminal window */

    // Print asterisks and welcome message
    PrintAsterisk(terminalWidth);
    PrintLeftPadding(terminalWidth, 23);
    printf("\e[1;34mWelcome to Phone-Dikhao\e[m\n");
    // printf("\e[1m\e[34mWelcome to Phone-Dikhao\e[m\n");
    PrintLeftPadding(terminalWidth, 28);
    printf("\e[34mA mobile showcasing platform\e[m\n");
    PrintAsterisk(terminalWidth);
}

void DeleteMobile() {}
void EditMobile() {}
void SearchMobile() {}
void ViewTopSellers() {}
void DisplayAll() {}
void InsertAtStart(ListNode_t **head, Mobile_t mobile)
{
    ListNode_t *new_node = (ListNode_t *)malloc(sizeof(ListNode_t));
    if (new_node == NULL)
    {
        printf("Memory not Allocated!\n");
        // return FAILURE;
        return;
    }
    // maxsize
    new_node->data = mobile;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        // return SUCCESS;
        return;
    }

    (*head)->prev = new_node;
    new_node->next = *head;
    *head = new_node;
}

void DisplayMainMenu()
{
    int choice;

    int mainCount = 1;
    while (mainCount <= 3)
    {
        // system("clear");
        InitDisplay();
        printf("1. Add Mobile\n");
        printf("2. Delete Mobile\n");
        printf("3. Edit Mobile\n");
        printf("4. Search Mobile\n");
        printf("5. View Top Sellers\n");
        printf("6. View all\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        GetIntInput(&choice);

        switch (choice)
        {
        case 1:
            AddMobile(&head);
            break;
        case 2:
            DeleteMobile();
            break;
        case 3:
            EditMobile();
            break;
        case 4:
            SearchMobile();
            break;
        case 5:
            ViewTopSellers();
            // printf("hello");
            break;
        case 6:
            // DisplayAll();
            Displaylist(head);
            break;
        case 7:
            printf("\n\e[1;33mExiting Application ...\e[m\n");
            exit(0);
            break;
        default:
            if (mainCount == 3)
            {
                printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
                exit(1);
            }
            printf("\n\e[31mInvalid choice. Please try again.\e[m\n");
            Escape();
            mainCount++;
            break;
        }
    }
}

void InitLinkedList(Mobile_t **head)
{
}
void AddMobile(ListNode_t **head)
{
    Mobile_t mobile;
    printf("Enter name: ");
    scanf(" %s", mobile.name);
    printf("Enter brand name: ");
    scanf(" %s", mobile.brandName);
    printf("Enter price: ");
    scanf(" %f", &mobile.price);
    printf("Enter name: ");
    scanf(" %d", &mobile.quantity);
    InsertAtStart(head, mobile);
}
int Displaylist(ListNode_t *head)
{

    if (head == NULL)
    {
        printf("Empty!\n");
        return SUCCESS;
    }

    while (head != NULL)
    {
        printf("%s | ", head->data.name);
        printf("%s | ", head->data.brandName);
        printf("%f | ", head->data.price);
        printf("%d\n", head->data.quantity);
        head = head->next;
    }
    printf("\n");
    head = NULL;
    // Escape();
    return SUCCESS;
}
int main()
{
    system("clear");
    InitDisplay();
    // Mobile_t *head = NULL;
    // ListNode_t *head = NULL;
    Mobile_t m1 = {"sneh", "shah", 123, 12312};
    Mobile_t m2 = {"sumo", "lugo", 123, 12312};
    Mobile_t m3 = {"sumo", "lugo", 123, 12312};
    Mobile_t m4 = {"sumo", "lugo", 123, 12312};
    Mobile_t m5 = {"sumo", "lugo", 123, 12312};
    // AddMobile(&head, m1);
    // AddMobile(&head, m2);
    InsertAtStart(&head, m1);
    InsertAtStart(&head, m2);
    InsertAtStart(&head, m3);
    InsertAtStart(&head, m4);
    InsertAtStart(&head, m5);
    // Displaylist(head);
    // InitLinkedList(&head);
    DisplayMainMenu();

    return SUCCESS;
}