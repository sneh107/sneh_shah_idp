/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file utils.c
 * @brief Utility functions for displaying information and managing user input.
 *
 * Provides utility functions for displaying formatted output, initializing the display,
 * handling user input, and managing the main menu display. Includes functions to print
 * asterisks, left padding, mobile phone details, and the main menu. Also includes functions
 * for getting integer and float input from the user, displaying the list of mobile phones,
 * and displaying the total number of mobiles in the store.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * May/23/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include "../inc/phone_dikhao.h"
extern ListNode_t *head;

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

void Escape()
{
    printf("\nPress \e[1;33mEnter\e[m to continue...\n");
    getchar();
    getchar();
}

int Displaylist()
{

    if (head == NULL)
    {
        printf("No mobiles in store\n");
        Escape();
        return SUCCESS;
    }

    ListNode_t *ptr = head;
    printf("\n");
    while (ptr != NULL)
    {
        PrintMobileDetails(ptr->data);
        ptr = ptr->next;
    }
    ptr = NULL;
    printf("\n");
    // head = NULL;
    Escape();
    return SUCCESS;
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

void GetFloatInput(float *num)
{
    while (scanf("%f", num) != 1)
    {
        printf("Invalid input. Enter a number: ");
        // Clear the input buffer
        while (getchar() != '\n')
            ;
    }
}

void PrintMobileDetails(Mobile_t mobile)
{
    printf("\n\e[1;34m%s\e[m\n\tBrand: %s\n\tPrice: %0.2f\n\tQuantity: %d\n", mobile.name, mobile.brandName, mobile.price, mobile.quantity);
}

void NumberOfMobiles()
{
    ListNode_t *temp = head;
    int mobile_count = 0;

    while (temp != NULL)
    {
        mobile_count++;
        temp = temp->next;
    }
    temp = NULL;
    printf("\n%d models of mobile present in store.\n", mobile_count);
    Escape();
}

void DisplayMainMenu()
{
    int choice;

    int mainCount = 1;
    while (mainCount <= 3)
    {
        system("clear");
        InitDisplay();
        printf("1. Add Mobile\n");
        printf("2. Delete Mobile\n");
        printf("3. Edit Mobile\n");
        printf("4. Search Mobile\n");
        printf("5. View all\n");
        printf("6. Total number of mobiles\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        GetIntInput(&choice);

        switch (choice)
        {
        case 1:
            AddMobile();
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
            // DisplayAll();
            Displaylist();
            break;
        case 6:
            NumberOfMobiles();
            break;
        case 7:
            printf("\n\e[1;33mExiting Application ...\e[m\n");
            DeleteList();
            exit(0);
            break;
        default:
            if (mainCount == 3)
            {
                printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
                DeleteList();
                exit(1);
            }
            printf("\n\e[31mInvalid choice. Please try again.\e[m\n");
            Escape();
            mainCount++;
            break;
        }
    }
}