#include "../../inc/includes.h"
#include "../../inc/common/utils.h"
#include "../../inc/searchMobile/searchMobile.h"
#include "../../inc/editMobile/editMobile.h"

extern int foundResult;
extern char tempstr[50];
int searchFlag;

int editMobile()
{
    int choice;
    int editCount = 1;

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
        searchFlag = 1;
        searchByMobileName();
        break;
    case 2:
        searchFlag = 2;
        searchByBrandName();
        break;
    case 3:
        return 0;
        break;
    case 4:
        printf("\n[1;33mExiting Application ...\e[m\n");
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
        escape();
        return -1;
    }

    int idToEdit;
    printf("Enter the ID of the mobile to edit: ");
    getIntInput(&idToEdit);

    if (performEdit(idToEdit) == -1)
    {
        // printf("\n\e[31mError occurred during editing.\e[m\n");
        // escape();
        return -1;
    }

    printf("\n\e[32mMobile details updated successfully.\e[m\n");
    escape();
}

int performEdit(int idToEdit)
{
    int readResult;
    FILE *file = openFile("./files/mobileData.bin", "rb+");
    if (file == NULL)
    {
        printf("\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return -1;
    }

    MobileData mobile;
    int found = 0;

    if (searchFlag == 1)
    {
        do
        {
            readResult = readMobile(file, &mobile);
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
            readResult = readMobile(file, &mobile);
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
        escape();
        fclose(file);
        return -1;
    }

    if (displayEditMenu(&mobile) == -1)
        return -1;

    fseek(file, -sizeof(MobileData), SEEK_CUR);

    fwrite(&mobile, sizeof(MobileData), 1, file);

    fclose(file);

    return 0;
}

int displayEditMenu(MobileData *mobile)
{
    int choice;
    int defaultCount = 1;

    while (defaultCount <= 3)
    {
        system("clear");
        initDisplay();
        printf("Mobile details:\n");
        printHeader();
        printMobileDetails(*mobile);
        printf("\nEdit Menu:\n");
        printf("1. Edit Price\n");
        printf("2. Edit Discount\n");
        printf("3. Edit Display Flag\n");
        printf("4. Edit Quantity\n");
        printf("5. Done\n");
        printf("6. Cancel\n");
        printf("Enter your choice: ");
        getIntInput(&choice);

        switch (choice)
        {
        case 1:
            printf("Enter new Price: ");
            getFloatInput(&mobile->price);
            while (mobile->price <= 0 || mobile->price >= 200000)
            // if (mobile.price <= 0 || mobile.price >= 200000)
            {
                printf("Enter valid price!\n");
                printf("Enter Price: ");
                getFloatInput(&mobile->price);
            }

            mobile->finalPrice = mobile->price - (mobile->price * (mobile->discount / 100));
            break;
        case 2:
            printf("Enter new Discount(in percentage): ");
            getFloatInput(&mobile->discount);
            while (mobile->discount <= 0)
            // if (mobile.discount <= 0)
            {
                printf("Enter valid Discount!\n");
                printf("Enter Discount(in percentage): ");
                getFloatInput(&mobile->discount);
            }
            mobile->finalPrice = mobile->price - (mobile->price * (mobile->discount / 100));
            break;
        case 3:
            printf("Enter new Display Flag (2: Outdated): ");
            getIntInput((int *)&mobile->displayFlag);
            while (mobile->displayFlag != 2)
            // if (mobile.displayFlag != 0 && mobile.displayFlag != 1)
            {
                printf("Enter valid display flag!\n");
                printf("Enter Display Flag (2: Outdated): ");
                getIntInput((int *)&mobile->displayFlag);
            }
            break;
        case 4:
            printf("Enter new Quantity: ");
            getIntInput(&mobile->quantity);
            while (mobile->quantity <= 0)
            // if (mobile.quantity <= 0)
            {
                printf("Enter valid Quantity!\n");
                printf("Enter Quantity: ");
                getIntInput(&mobile->quantity);
            }
            break;
        case 5:
            if (confirm() == -1)
                return -1;
            return 0;
            break;
        case 6:
            printf("Operation Cancelled!\n");
            escape();
            return -1;
            break;
        default:
            if (defaultCount == 3)
            {
                printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
                exit(1);
            }
            printf("\e[31mInvalid choice.\e[m\n");
            escape();
            defaultCount++;
            break;
        }
    }
}