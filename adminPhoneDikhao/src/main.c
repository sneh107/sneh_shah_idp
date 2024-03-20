// Shree Ganeshay Namah!

// gcc main.c common/utils.c addMobile/addMobile.c deleteMobile/deleteMobile.c searchMobile/searchMobile.c editMobile/editMobile.c -o app

// #include "../inc/includes.h"
#include "../inc/main.h"
#include "../inc/common/utils.h"
#include "../inc/addMobile/addMobile.h"
#include "../inc/deleteMobile/deleteMobile.h"
#include "../inc/editMobile/editMobile.h"
#include "../inc/searchMobile/searchMobile.h"

int main()
{
    system("clear");
    InitDisplay();
    if (Login() == -1)
        return FAILURE;
    DisplayMainMenu();
    return SUCCESS;
}

int Login()
{
    char username[50];
    char password[50];
    int loginCount = 0;
    while (loginCount < 3)
    {
        printf("Enter Admin Username: ");
        scanf(" %49[^\n]s", username);
        printf("Enter Admin Password: ");
        scanf(" %49[^\n]s", password);

        if (ValidateCredentials(username, password) == -1)
        {
            printf("\n\e[31mInvalid credentials. Please try again.\e[m\n");
            loginCount++;
        }
        else
        {
            printf("\n\e[1;32mLogin Successful!\e[m\n");
            sleep(1);
            return SUCCESS;
        }
    }
    printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
    return FAILURE;
}
int ValidateCredentials(char *username, char *password)
{
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
        return SUCCESS;
    else
        return FAILURE;
}

void DisplayMainMenu()
{
    int choice;

    int mainCount = 1;
    while (mainCount <= 3)
    {
        system("clear");
        InitDisplay();
        printf("1. Add Mobile\n");
        printf("2. Delete Mobile\n");
        printf("3. Edit Mobile\n");
        printf("4. Search Mobile\n");
        printf("5. View Top Sellers\n");
        printf("6. View all\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        GetIntInput(&choice);

        switch (choice)
        {
        case 1:
            AddMobile();
            break;
        case 2:
            DeleteMobile();
            break;
        case 3:
            EditMobile();
            break;
        case 4:
            SearchMobile();
            break;
        case 5:
            ViewTopSellers();
            // printf("hello");
            break;
        case 6:
            DisplayAll();
            break;
        case 7:
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

int ViewTopSellers()
{
    MobileData_t mobile;
    int readResult;
    FILE *file = OpenFile("./files/mobileData.bin", "rb");
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
    Escape();
    return SUCCESS;
}

int DisplayAll()
{
    MobileData_t mobile;
    int readResult;
    FILE *file = OpenFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }
    printf("\n");
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1)
        {
            PrintMobileDetails(mobile);
        }
    } while (readResult == 1);

    fclose(file);
    Escape();
    return SUCCESS;
}