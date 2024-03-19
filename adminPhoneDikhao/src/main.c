// Shree Ganeshay Namah!

// gcc main.c common/utils.c addMobile/addMobile.c deleteMobile/deleteMobile.c searchMobile/searchMobile.c editMobile/editMobile.c -o app

#include "../inc/includes.h"
#include "../inc/struct.h"
#include "../inc/main.h"
#include "../inc/utils.h"

int main()
{
    system("clear");
    initDisplay();
    // if (!login())
    //     return FAILURE;
    displayMainMenu();
    return FAILURE;
}

int login()
{
    char username[20];
    char password[20];
    int loginCount = 0;
    while (loginCount < 3)
    {
        printf("Enter Admin Username: ");
        scanf(" %[^\n]s", username);
        printf("Enter Admin Password: ");
        scanf(" %[^\n]s", password);

        if (!validateCredentials(username, password))
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
int validateCredentials(char *username, char *password)
{
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
        return SUCCESS;
    else
        return FAILURE;
}

int displayMainMenu()
{
    int choice;

    int mainCount = 1;
    while (mainCount <= 3)
    {
        system("clear");
        initDisplay();
        printf("1. Add Mobile\n");
        printf("2. Delete Mobile\n");
        printf("3. Edit Mobile\n");
        printf("4. Search Mobile\n");
        printf("5. View Top Sellers\n");
        printf("6. View all\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        getIntInput(&choice);

        switch (choice)
        {
        case 1:
            addMobile();
            break;
        case 2:
            deleteMobile();
            break;
        case 3:
            editMobile();
            break;
        case 4:
            searchMobile();
            break;
        case 5:
            viewTopSellers();
            // printf("hello");
            break;
        case 6:
            displayAll();
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
            mainCount++;
            break;
        }
    }
}

int viewTopSellers()
{
    MobileData mobile;
    int readResult;
    FILE *file = openFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return FAILURE;
    }
    printHeader();
    do
    {
        readResult = readMobile(file, &mobile);
        if (readResult == 1 && mobile.displayFlag == 3)
        {
            printMobileDetails(mobile);
        }
    } while (readResult == 1);

    fclose(file);
    escape();
}

int displayAll()
{
    MobileData mobile;
    int readResult;
    FILE *file = openFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return FAILURE;
    }
    printf("\n");
    printHeader();
    do
    {
        readResult = readMobile(file, &mobile);
        if (readResult == 1)
        {
            printMobileDetails(mobile);
        }
    } while (readResult == 1);

    fclose(file);
    escape();
}