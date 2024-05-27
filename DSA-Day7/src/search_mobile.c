/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file search_mobile.c
 * @brief Functions for searching mobile phone records.
 *
 * Contains functions to search for mobile phone records by name or price range.
 * Includes functions to search by mobile name, search by price range, and a main
 * function to provide options for searching and handle user input.
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

int SearchByMobileName()
{
    char mobileName[50];
    int flag = 0;
    printf("Enter Mobile Name to search: ");
    scanf(" %[^\n]s", mobileName);
    if (head == NULL)
    {
        printf("No mobiles in store\nOperation Cancelled...\n");
        Escape();
        return flag;
    }

    ListNode_t *temp = head;

    while (temp != NULL)
    {
        if (strcasecmp(mobileName, temp->data.name) == 0)
        {
            flag = 1;
            PrintMobileDetails(temp->data);
            Escape();
        }

        temp = temp->next;
    }
    temp = NULL;
    if (flag == 0)
    {
        printf("\nNo matching mobile found!\n");
        Escape();
    }
    return flag;
}

int SearchByPriceRange()
{
    if (head == NULL)
    {
        printf("No mobiles in store\nOperation Cancelled...\n");
        Escape();
        return FAILURE;
    }
    float min_price = 0, max_price = 0;
    int found_mobiles = 0;
    printf("Enter minimum price: ");
    GetFloatInput(&min_price);

    printf("Enter maximum price: ");
    GetFloatInput(&max_price);

    ListNode_t *temp = head;

    while (temp != NULL)
    {
        if (temp->data.price >= min_price && temp->data.price <= max_price)
        {
            found_mobiles++;
            PrintMobileDetails(temp->data);
        }

        temp = temp->next;
    }
    temp = NULL;
    if (found_mobiles == 0)
    {
        printf("\nNo matching mobile found!\n");
        Escape();
    }
    else
    {
        printf("\n%d mobiles found!\n", found_mobiles);
        Escape();
    }
    return SUCCESS;
}

int SearchMobile()
{
    int choice = 0;
    int searchCount = 1;

    while (searchCount <= 3)
    {
        system("clear");
        InitDisplay();
        printf("\nSearch Options:\n");
        printf("1. Search by Mobile Name\n");
        printf("2. Search by Pricerange\n");
        printf("3. Back\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        GetIntInput(&choice);

        switch (choice)
        {
        case 1:
            SearchByMobileName();
            break;

        case 2:
            SearchByPriceRange();
            break;
        case 3:
            return SUCCESS;
            break;
        case 4:
            printf("\n\e[1;33mExiting Application ...\e[m\n");
            DeleteList();
            exit(0);
            break;

        default:
            if (searchCount == 3)
            {
                printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
                DeleteList();
                exit(1);
            }
            printf("\n\e[31mInvalid choice. Please try again.\e[m\n");
            Escape();
            searchCount++;
            break;
        }
    }
    return SUCCESS;
}
