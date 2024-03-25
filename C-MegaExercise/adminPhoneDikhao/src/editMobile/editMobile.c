/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file editMobile.c
 * @brief Functions for editing mobile data in the database.
 *
 * This file contains functions responsible for editing mobile data in the database.
 * It includes functions for searching mobiles by name or brand, performing edits,
 * and displaying edit menus for price, discount, display flag, and quantity.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Mar/15/2024, Sneh Shah, Created
 *
 ******************************************************************************/
#include "../../inc/common/utils.h"
#include "../../inc/searchMobile/searchMobile.h"
#include "../../inc/editMobile/editMobile.h"

int EditMobile()
{
    int choice;
    int editCount = 1;

    system("clear");
    InitDisplay();
    printf("\nSearch Options:\n");
    printf("1. Search by Mobile Name\n");
    printf("2. Search by Brand Name\n");
    printf("3. Back\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    GetIntInput(&choice);

    switch (choice)
    {
    case 1:
        searchFlag = 1;
        SearchByMobileName();
        break;
    case 2:
        searchFlag = 2;
        SearchByBrandName();
        break;
    case 3:
        return SUCCESS;
        break;
    case 4:
        printf("\n\e[1;33mExiting Application ...\e[m\n");
        exit(0);
        break;
    default:
        if (editCount == 3)
        {
            printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
            exit(1);
        }
        printf("\n\e[31mInvalid choice. Please try again.\e[m\n");
        editCount++;
        break;
    }

    if (foundResult == -1)
    {
        Escape();
        return FAILURE;
    }

    int idToEdit;
    printf("Enter the ID of the mobile to edit: ");
    GetIntInput(&idToEdit);

    if (PerformEdit(idToEdit) == -1)
    {
        // printf("\n\e[31mError occurred during editing.\e[m\n");
        // Escape();
        return FAILURE;
    }

    printf("\n\e[32mMobile details updated successfully.\e[m\n");
    Escape1();
    return SUCCESS;
}

int PerformEdit(int idToEdit)
{
    int readResult;
    FILE *file = OpenFile("../files/mobileData.bin", "rb+");
    if (file == NULL)
    {
        printf("\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    MobileData_t mobile;
    int found = 0;

    if (searchFlag == 1)
    {
        do
        {
            readResult = ReadMobile(file, &mobile);
            if (readResult == 1 && mobile.id == idToEdit && strcasecmp(mobile.name, tempstr) == 0)
            {
                found = 1;
                break;
            }
        } while (readResult == 1);
    }
    else if (searchFlag == 2)
    {
        do
        {
            readResult = ReadMobile(file, &mobile);
            if (readResult == 1 && mobile.id == idToEdit && strcasecmp(mobile.brandName, tempstr) == 0)
            {
                found = 1;
                break;
            }
        } while (readResult == 1);
    }

    if (found == 0)
    {
        printf("\e[31mMobile with ID %d not found.\e[m\n", idToEdit);
        Escape();
        fclose(file);
        return FAILURE;
    }

    if (DisplayEditMenu(&mobile) == -1)
        return FAILURE;

    fseek(file, -sizeof(MobileData_t), SEEK_CUR);

    fwrite(&mobile, sizeof(MobileData_t), 1, file);

    fclose(file);

    return SUCCESS;
}

int DisplayEditMenu(MobileData_t *mobile)
{
    int choice;
    int defaultCount = 1;

    while (defaultCount <= 3)
    {
        system("clear");
        InitDisplay();
        printf("Mobile details:\n");
        PrintHeader();
        PrintMobileDetails(*mobile);
        printf("\nEdit Menu:\n");
        printf("1. Edit Price\n");
        printf("2. Edit Discount\n");
        printf("3. Edit Display Flag\n");
        printf("4. Edit Quantity\n");
        printf("5. Done\n");
        printf("6. Cancel\n");
        printf("Enter your choice: ");
        GetIntInput(&choice);

        switch (choice)
        {
        case 1:
            printf("Enter new Price: ");
            GetFloatInput(&mobile->price);
            while (mobile->price <= 0 || mobile->price >= 200000)
            // if (mobile.price <= 0 || mobile.price >= 200000)
            {
                printf("Enter valid price!\n");
                printf("Enter Price: ");
                GetFloatInput(&mobile->price);
            }

            mobile->finalPrice = mobile->price - (mobile->price * (mobile->discount / 100));
            break;
        case 2:
            printf("Enter new Discount(in percentage): ");
            GetFloatInput(&mobile->discount);
            while (mobile->discount <= 0)
            // if (mobile.discount <= 0)
            {
                printf("Enter valid Discount!\n");
                printf("Enter Discount(in percentage): ");
                GetFloatInput(&mobile->discount);
            }
            mobile->finalPrice = mobile->price - (mobile->price * (mobile->discount / 100));
            break;
        case 3:
            printf("Enter new Display Flag (2: Outdated): ");
            GetIntInput((int *)&mobile->displayFlag);
            while (mobile->displayFlag != 2)
            // if (mobile.displayFlag != 0 && mobile.displayFlag != 1)
            {
                printf("Enter valid display flag!\n");
                printf("Enter Display Flag (2: Outdated): ");
                GetIntInput((int *)&mobile->displayFlag);
            }
            break;
        case 4:
            printf("Enter new Quantity: ");
            GetIntInput(&mobile->quantity);
            while (mobile->quantity <= 0)
            // if (mobile.quantity <= 0)
            {
                printf("Enter valid Quantity!\n");
                printf("Enter Quantity: ");
                GetIntInput(&mobile->quantity);
            }
            break;
        case 5:
            if (Confirm() == -1)
                return FAILURE;
            return SUCCESS;
            break;
        case 6:
            printf("Operation Cancelled!\n");
            Escape();
            return FAILURE;
            break;
        default:
            if (defaultCount == 3)
            {
                printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
                exit(1);
            }
            printf("\e[31mInvalid choice.\e[m\n");
            Escape();
            defaultCount++;
            break;
        }
    }
    return SUCCESS;
}