#include "../../inc/includes.h"
#include "../../inc/struct.h"
#include "../../inc/searchMobile.h"
#include "../../inc/utils.h"

int foundResult;

void searchMobile()
{
    system("clear");
    initDisplay();
    displaySearchMenu();
    // escape();
}

int displaySearchMenu()
{
    int choice;
    int searchCount = 1;

    while (searchCount <= 3)
    {
        system("clear");
        initDisplay();
        printf("\nSearch Options:\n");
        printf("1. Search by Mobile Name\n");
        printf("2. Search by Brand Name\n");
        printf("3. Back\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        getIntInput(&choice);

        switch (choice)
        {
        case 1:
            searchByMobileName();
            escape();
            break;
        case 2:
            searchByBrandName();
            escape();
            break;
        case 3:
            return FAILURE;
            break;
        case 4:
            printf("\n\e[1;33mExiting Application ...\e[m\n");
            exit(0);
            break;
        default:
            if (searchCount == 3)
            {
                printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
                exit(1);
            }
            printf("\n\e[31mInvalid choice. Please try again.\e[m\n");
            searchCount++;
            return FAILURE;
            break;
        }
    }
}

int searchByMobileName()
{
    char mobileName[50];
    MobileData mobile;
    int readResult;

    printf("Enter Mobile Name to search: ");
    scanf(" %[^\n]", mobileName);

    FILE *file = openFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return FAILURE;
    }

    int foundMobiles = 0;
    printHeader();
    do
    {
        readResult = readMobile(file, &mobile);
        if (readResult == 1 && strcasecmp(mobile.name, mobileName) == 0)
        {
            printMobileDetails(mobile);
            foundMobiles++;
        }
    } while (readResult == 1);

    fclose(file);
    foundResult = mobileFound(foundMobiles);
}

int searchByBrandName()
{
    char brandName[50];
    MobileData mobile;
    int readResult;

    printf("Enter Brand Name to search: ");
    scanf(" %[^\n]", brandName);

    FILE *file = openFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return FAILURE;
    }
    int foundMobiles = 0;
    printHeader();
    do
    {
        readResult = readMobile(file, &mobile);
        if (readResult == 1 && strcasecmp(mobile.brandName, brandName) == 0)
        {
            printMobileDetails(mobile);
            foundMobiles++;
        }
    } while (readResult == 1);

    fclose(file);
    foundResult = mobileFound(foundMobiles);
}

int mobileFound(int foundMobiles)
{
    if (foundMobiles == 0)
    {
        printf("\n\e[31mNo matching mobiles found.\e[m\n");
        return FAILURE;
        // escape();
    }
    else
    {
        printf("\n\e[32m%d\e[m Mobiles Found.\n", foundMobiles);
        return SUCCESS;
        // escape();
    }
}