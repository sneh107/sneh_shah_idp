/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file main.c
 * @brief Main application entry point and user interface functions.
 *
 * This file contains the main function and functions for displaying the main menu
 * and viewing top sellers. It includes options for buying top sellers, searching
 * by price range, and searching by configuration.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Mar/20/2024, Sneh Shah, Created
 *
 ******************************************************************************/
// Shree Ganeshay Namah

#include "../inc/common/utils.h"
#include "../inc/main.h"
#include "../inc/buy/buy_top_sellers.h"
#include "../inc/search/search_mobile.h"

int main()
{
    DisplayMainMenu();
    return SUCCESS;
}

int ViewTopSellers()
{
    MobileData_t mobile;
    int readResult;
    FILE *file = OpenFile("../files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && mobile.displayFlag == 3)
        {
            PrintMobileDetails(mobile);
        }
    } while (readResult == 1);

    fclose(file);
    return SUCCESS;
}

void DisplayMainMenu()
{
    int choice;
    int mainCount = 1;
    while (mainCount <= 3)
    {

        system("clear");
        InitDisplay();
        printf("\e[1;36mBest Sellers:\e[m\n");
        ViewTopSellers();
        printf("\n\e[1;36mMain Menu:\e[m\n");
        printf("1. Buy Top Sellers\n");
        printf("2. Search by Price Range\n");
        printf("3. Search by Configuration\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        GetIntInput(&choice);

        switch (choice)
        {
        case 1:
            BuyTopSellers();
            break;
        case 2:
            FilterByPrice();
            break;
        case 3:
            FilterByConfig();
            break;
        case 4:
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