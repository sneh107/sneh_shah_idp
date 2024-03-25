/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file utils.c
 * @brief Utility functions for Phone-Dikhao application.
 *
 * This file contains utility functions used in the Phone-Dikhao application.
 * It includes functions for initializing the display, printing headers and mobile
 * details, opening files, reading mobile data from files, confirming user actions,
 * and handling escape sequences.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Mar/14/2024, Sneh Shah, Created
 *
 ******************************************************************************/
#include "../../inc/common/utils.h"

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

FILE *OpenFile(char *fileName, char *mode)
{
    FILE *file = fopen(fileName, mode);
    return file;
}

int ReadMobile(FILE *file, MobileData_t *mobile)
{
    int readResult = fread(mobile, sizeof(MobileData_t), 1, file);
    if (readResult == 1)
    {
        return 1;
    }
    else if (feof(file))
    {
        return FAILURE;
    }
    else
    {
        printf("\n\e[31mError reading mobile from file.\e[m\n");
        Escape();
        return FAILURE;
    }
}

int Confirm()
{
    char confirmation;
    printf("Confirm? \e[1;33m(y/n):\e[m ");
    scanf(" %c", &confirmation);
    while (getchar() != '\n')
        ;

    if (confirmation == 'n' || confirmation == 'N')
    {

        printf("\n\e[31mOperation cancelled.\e[m\n");
        Escape1();
        return FAILURE;
    }
    else if (confirmation == 'y' || confirmation == 'Y')
    {
        return SUCCESS;
    }
    else
    {
        printf("\n\e[31mInvalid Input!\e[m\n");
        Escape1();
        return FAILURE;
    }
}

void PrintHeader()
{
    printf("%-3s %-20s %-10s %-10s %-12s %-10s %-15s %-8s %-5s %-8s %-12s %-15s %-6s\n", "MID", "Name", "BrandName", "Price", "Discount(%)", "FinalPrice", "Flag", "Quantity", "Count", "RAM(Gb)", "Storage(GB)", "Chipset", "Camera(MP)");
}

void PrintMobileDetails(MobileData_t mobile)
{
    char flag[50];

    switch (mobile.displayFlag)
    {
    case new:
        strcpy(flag, "New");
        break;
    case refurbished:
        strcpy(flag, "Refurbished");
        break;
    case outdated:
        strcpy(flag, "Outdated");
        break;
    case mostPurchased:
        strcpy(flag, "Most Purchased");
        break;
    case outOfStock:
        strcpy(flag, "Out of Stock");
        break;
    default:
        break;
    }

    printf("%-3d %-20s %-10s %-10.2f %-12.2f %-10.2f %-15s %-8d %-5d %-8d %-12d %-15s %-6d\n", mobile.id, mobile.name, mobile.brandName, mobile.price, mobile.discount, mobile.finalPrice, flag, mobile.quantity, mobile.count, mobile.config.ram, mobile.config.storage, mobile.config.chipset, mobile.config.camera);
}

void Escape()
{
    printf("\nPress \e[1;33mEnter\e[m to continue...\n");
    getchar();
    getchar();
}

void Escape1()
{
    printf("\nPress \e[1;33mEnter\e[m to continue...\n");
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