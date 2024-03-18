#include "../../inc/includes.h"
#include "../../inc/struct.h"
#include "../../inc/utils.h"
void displayOutdatedMobiles();

int deleteMobile()
{
    displayOutdatedMobiles();

    int idToDelete;
    // printf("Enter the ID of the mobile to delete: ");
    // scanf("%d", &idToDelete);
    if (!isIdValid(&idToDelete))
    {
        return FAILURE;
    }

    if (!confirm())
    {
        return FAILURE;
    }

    FILE *file = openFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return FAILURE;
    }

    FILE *tempFile = openFile("./files/tempMobileData.bin", "wb");
    if (tempFile == NULL)
    {
        printf("\n\e[31mError: Unable to open tempMobileData.bin file.\e[m\n");
        escape();
        fclose(file);
        return FAILURE;
    }

    MobileData mobile;
    while (readMobile(file, &mobile))
    {
        if (mobile.id != idToDelete)
        {
            fwrite(&mobile, sizeof(MobileData), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("./files/mobileData.bin");
    rename("./files/tempMobileData.bin", "./files/mobileData.bin");

    printf("\n\e[32mMobile record with ID %d deleted successfully.\e[m\n", idToDelete);
    escape();
}

void displayOutdatedMobiles()
{
    MobileData mobile;
    int readResult;
    FILE *file = openFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return;
    }
    printf("\n");
    printHeader();
    do
    {
        readResult = readMobile(file, &mobile);
        if (readResult == 1 && mobile.displayFlag == 2)
        {
            printMobileDetails(mobile);
        }
    } while (readResult == 1);
    printf("\n");

    fclose(file);
    // escape();
}