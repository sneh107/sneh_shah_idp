#include "../../inc/includes.h"
#include "../../inc/struct.h"
#include "../../inc/utils.h"
#include "../../inc/searchMobile.h"
#include "../../inc/editMobile.h"

extern int foundResult;

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
        searchByMobileName();
        break;
    case 2:
        searchByBrandName();
        break;
    case 3:
        return FAILURE;
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

    if (foundResult == 0)
    {
        escape();
        return FAILURE;
    }

    int idToEdit;
    printf("Enter the ID of the mobile to edit: ");
    getIntInput(&idToEdit);

    if (!performEdit(idToEdit))
    {
        printf("\n\e[31mError occurred during editing.\e[m\n");
        escape();
        return FAILURE;
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
        return FAILURE;
    }

    MobileData mobile;
    int found = 0;

    do
    {
        readResult = readMobile(file, &mobile);
        if (readResult == 1 && mobile.id == idToEdit)
        {
            found = 1;
            break;
        }
    } while (readResult == 1);

    if (!found)
    {
        printf("\e[31mMobile with ID %d not found.\e[m\n", idToEdit);
        fclose(file);
        return FAILURE;
    }

    if (!displayEditMenu(&mobile))
        return FAILURE;

    fseek(file, -sizeof(MobileData), SEEK_CUR);

    fwrite(&mobile, sizeof(MobileData), 1, file);

    fclose(file);

    return SUCCESS;
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
            mobile->finalPrice = mobile->price - (mobile->price * (mobile->discount / 100));
            break;
        case 2:
            printf("Enter new Discount(in percentage): ");
            getFloatInput(&mobile->discount);
            mobile->finalPrice = mobile->price - (mobile->price * (mobile->discount / 100));
            break;
        case 3:
            printf("Enter new Display Flag (0: New, 1: Refurbished, 2: Outdated, 3: Most Purchased, 4: Out of Stock): ");
            getIntInput((int *)&mobile->displayFlag);
            break;
        case 4:
            printf("Enter new Quantity: ");
            getIntInput(&mobile->quantity);
            break;
        case 5:
            if (!confirm())
                return FAILURE;
            return SUCCESS;
            break;
        case 6:
            printf("Operation Cancelled!\n");
            return FAILURE;
            break;
        default:
            if (defaultCount == 3)
            {
                printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
                exit(1);
            }
            printf("\e[31mInvalid choice.\e[m\n");
            defaultCount++;
            break;
        }
    }
}