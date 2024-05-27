/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file delete_mobile.c
 * @brief Contains functions to delete mobile phone records from the store.
 *
 * Defines functions for deleting individual mobile phone records and the entire
 * linked list of mobile phone records. Utilizes the "phone_dikhao.h" header file
 * and the global variable head to access the linked list.
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

int DeleteMobile()
{
    if (head == NULL)
    {
        printf("\nNothing to delete!\nNo mobiles in store!\n");
        Escape();
        return SUCCESS;
    }

    char mobile_name[50];
    printf("Enter name of mobile to delete: ");
    scanf(" %[^\n]s", mobile_name);
    ListNode_t *ptr = head;
    while (strcasecmp(mobile_name, ptr->data.name) != 0)
    {
        if (ptr->next == NULL)
        {
            printf("\nMobile not found!\n");
            Escape();
            ptr = NULL;
            return FAILURE;
        }

        ptr = ptr->next;
    }
    if (ptr->next == NULL && ptr->prev == NULL)
    {
        free(ptr);
        ptr = NULL;
        printf("\n\e[32mMobile record deleted successfully.\e[m\n");
        Escape();
        head = NULL;
        return SUCCESS;
    }
    if (ptr->next == NULL)
    {
        ListNode_t *temp = ptr->prev;
        temp->next = NULL;
        free(ptr);
        ptr = NULL;
        printf("\n\e[32mMobile record deleted successfully.\e[m\n");
        Escape();
        return SUCCESS;
    }
    if (ptr->prev == NULL)
    {
        ListNode_t *temp = ptr;
        ptr = ptr->next;
        ptr->prev = NULL;
        head = ptr;
        ptr = NULL;
        free(temp);
        temp = NULL;
        printf("\n\e[32mMobile record deleted successfully.\e[m\n");
        Escape();
        return SUCCESS;
    }
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    free(ptr);
    ptr = NULL;
    printf("\n\e[32mMobile record deleted successfully.\e[m\n");
    Escape();
    return SUCCESS;
}

void DeleteList()
{
    while (head != NULL)
    {
        ListNode_t *temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }
    head = NULL;
}