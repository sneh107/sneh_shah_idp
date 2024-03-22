// #include "../../inc/includes.h"
#include "../../inc/searchMobile/searchMobile.h"
#include "../../inc/common/utils.h"

void SearchMobile()
{
    system("clear");
    InitDisplay();
    DisplaySearchMenu();
    // Escape();
}

int DisplaySearchMenu()
{
    int choice;
    int searchCount = 1;

    while (searchCount <= 3)
    {
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
            SearchByMobileName();
            Escape();
            break;
        case 2:
            SearchByBrandName();
            Escape();
            break;
        case 3:
            return SUCCESS;
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
            Escape();
            searchCount++;
            // return FAILURE;
            break;
        }
    }
    return SUCCESS;
}

int SearchByMobileName()
{
    char mobileName[50];
    MobileData_t mobile;
    int readResult;

    printf("Enter Mobile Name to search: ");
    scanf(" %[^\n]", mobileName);
    strcpy(tempstr, mobileName);

    FILE *file = OpenFile("../files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    int foundMobiles = 0;
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && strcasecmp(mobile.name, mobileName) == 0)
        {
            PrintMobileDetails(mobile);
            foundMobiles++;
        }
    } while (readResult == 1);

    fclose(file);
    foundResult = MobileFound(foundMobiles);
    return SUCCESS;
}

int SearchByBrandName()
{
    char brandName[50];
    MobileData_t mobile;
    int readResult;

    printf("Enter Brand Name to search: ");
    scanf(" %[^\n]", brandName);
    strcpy(tempstr, brandName);

    FILE *file = OpenFile("../files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }
    int foundMobiles = 0;
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && strcasecmp(mobile.brandName, brandName) == 0)
        {
            PrintMobileDetails(mobile);
            foundMobiles++;
        }
    } while (readResult == 1);

    fclose(file);
    foundResult = MobileFound(foundMobiles);
    return SUCCESS;
}

int MobileFound(int foundMobiles)
{
    if (foundMobiles == 0)
    {
        printf("\n\e[31mNo matching mobiles found.\e[m\n");
        return FAILURE;
        // Escape();
    }
    else
    {
        printf("\n\e[32m%d\e[m Mobiles Found.\n", foundMobiles);
        return 1;
        // Escape();
    }
}