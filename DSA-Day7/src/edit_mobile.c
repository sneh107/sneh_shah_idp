/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 *
 * @file edit_mobile.c
 * @brief Functions for editing mobile phone records.
 *
 * Defines a function to update the stock quantity of a mobile phone in the store.
 * Prompts the user to enter the name of the mobile phone for which they want to update
 * the stock quantity. Searches for the mobile phone in the linked list and allows the user
 * to enter the updated quantity. Validates the input and updates the quantity if valid.
 *
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

int EditMobile()
{
    if (head == NULL)
    {
        printf("No mobiles in store\nOperation Cancelled...\n");
        Escape();
        return FAILURE;
    }
    char mobileName[50];
    int flag = 0;
    printf("Enter Mobile Name for which you want to update stocks: ");
    scanf(" %[^\n]s", mobileName);
    ListNode_t *temp = head;

    while (temp != NULL)
    {
        if (strcasecmp(mobileName, temp->data.name) == 0)
        {
            flag = 1;
            PrintMobileDetails(temp->data);
            break;
        }

        temp = temp->next;
    }
    if (flag == 0)
    {
        printf("\nNo matching mobile found!\n");
        Escape();
        return FAILURE;
    }
    printf("Enter updated quantity: ");
    GetIntInput(&temp->data.quantity);
    while (temp->data.quantity <= 0)
    {
        printf("Enter valid Quantity!\n");
        printf("Enter Quantity: ");
        GetIntInput(&temp->data.quantity);
    }
    temp = NULL;
    printf("\n\e[32mMobile details updated successfully.\e[m\n");
    Escape();
    return SUCCESS;
}