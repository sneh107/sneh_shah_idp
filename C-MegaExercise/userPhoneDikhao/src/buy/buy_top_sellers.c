/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file buy_top_sellers.c
 * @brief Functions for buying top-selling mobiles.
 *
 * This file contains functions for buying top-selling mobiles. It includes
 * functions for displaying top sellers, processing purchases, and updating
 * mobile and customer data files accordingly.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Mar/21/2024, Sneh Shah, Created
 *
 ******************************************************************************/
#include "../../inc/main.h"
#include "../../inc/common/utils.h"
#include "../../inc/buy/buy_top_sellers.h"

int BuyTopSellers()
{
    char input_name[50];
    char customer_name[50];
    int buy_quantity;
    system("clear");
    InitDisplay();
    printf("\e[36mBest Sellers:\e[m\n");
    ViewTopSellers();
    if (IsBuy() == -1)
        return FAILURE;
    printf("\nEnter the name of the mobile to buy: ");
    scanf(" %49[^\n]s", input_name);

    FILE *file = OpenFile("../files/mobileData.bin", "rb+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    int mobile_found;
    MobileData_t mobile;

    while (ReadMobile(file, &mobile) == 1)
    {
        if (strcasecmp(mobile.name, input_name) == 0 && mobile.displayFlag == mostPurchased)
        {
            mobile_found = 1;
            break;
        }
    }

    // fclose(file);

    if (mobile_found != 1)
    {
        fclose(file);
        printf("\n\e[31mInvalid Name.\e[m\n");
        Escape();
        return FAILURE;
    }

    AskCustomerDetails(customer_name, &buy_quantity);
    ProcessPurchase(&mobile, file, input_name, customer_name, buy_quantity);
    return SUCCESS;
}

int ProcessPurchase(MobileData_t *mobile, FILE *file, char input_name[], char customer_name[], int buy_quantity)
{
    if (buy_quantity > mobile->quantity)
    {
        fclose(file);
        printf("Not Enough Quantity!\n");
        Escape();
        return FAILURE;
    }

    if (Confirm() == -1)
    {
        fclose(file);
        return FAILURE;
    }

    mobile->count = mobile->count + buy_quantity;
    if (mobile->count >= 5)
    {
        mobile->displayFlag = mostPurchased;
    }
    mobile->quantity = mobile->quantity - buy_quantity;
    if (mobile->quantity == 0)
    {
        mobile->displayFlag = outOfStock;
    }

    fseek(file, -sizeof(MobileData_t), SEEK_CUR);

    fwrite(mobile, sizeof(MobileData_t), 1, file);

    fclose(file);

    file = OpenFile("../files/customer_data.txt", "a");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open customer_data.txt file.\e[m\n");
        Escape();
        return FAILURE;
    }

    fprintf(file, "%-20s %-20s %-20d\n", customer_name, input_name, buy_quantity);

    fclose(file);
    printf("Mobile Bought Succeessfully");
    Escape();
    return SUCCESS;
}