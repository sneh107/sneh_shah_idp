/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file add_mobile.c
 * @brief Contains functions to add and initialize mobile phones.
 *
 * Defines functions for adding mobile phones to the store, initializing
 * the linked list with default mobile phones, and adding new mobile phones
 * with user input.
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

int InsertMobile(Mobile_t mobile)
{
    ListNode_t *new_node = (ListNode_t *)malloc(sizeof(ListNode_t));
    if (new_node == NULL)
    {
        printf("Memory not Allocated!\n");
        Escape();
        return FAILURE;
    }
    // maxsize
    new_node->data = mobile;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (head == NULL)
    {
        head = new_node;
        return SUCCESS;
    }

    head->prev = new_node;
    new_node->next = head;
    head = new_node;
    new_node = NULL;
    return SUCCESS;
}

void InitLinkedList()
{
    Mobile_t m1 = {"Moto G64 5G", "Motorola ", 13999, 10};
    Mobile_t m2 = {"Note 13 Pro", "Redmi", 24999, 50};
    Mobile_t m3 = {"Galaxy S21 FE 5G", "Samsung", 29999, 15};
    Mobile_t m4 = {"Galaxy S24 Ultra 5G", "Samsung", 139999, 5};
    Mobile_t m5 = {"Nord CE 4 5G", "OnePlus", 30999, 10};
    InsertMobile(m1);
    InsertMobile(m2);
    InsertMobile(m3);
    // InsertMobile(m4);
    // InsertMobile(m5);
}

int AddMobile()
{
    Mobile_t mobile;
    printf("Enter Mobile Name: ");
    scanf(" %[^\n]s", mobile.name);

    ListNode_t *temp = head;

    while (temp != NULL)
    {
        if (strcasecmp(mobile.name, temp->data.name) == 0)
        {
            printf("\nMobile Already present!\n");
            Escape();
            return FAILURE;
        }

        temp = temp->next;
    }
    temp = NULL;

    printf("Enter Brand Name: ");
    scanf(" %[^\n]s", mobile.brandName);
    printf("Enter Price: ");
    GetFloatInput(&mobile.price);
    while (mobile.price <= 0 || mobile.price >= 200000)
    {
        printf("Enter valid price!\n");
        printf("Enter Price: ");
        GetFloatInput(&mobile.price);
    }

    printf("Enter Quantity: ");
    GetIntInput(&mobile.quantity);
    while (mobile.quantity <= 0)
    {
        printf("Enter valid Quantity!\n");
        printf("Enter Quantity: ");
        GetIntInput(&mobile.quantity);
    }
    if (!InsertMobile(mobile))
    {
        printf("\n\e[32mMobile added successfully!\e[m\n");
        Escape();
    }
    return SUCCESS;
}