#include "../../inc/includes.h"
#include "../../inc/common/utils.h"
void displayOutdatedMobiles();
int isIdValid(int *id);

int deleteMobile()
{
    displayOutdatedMobiles();

    int idToDelete;
    // printf("Enter the ID of the mobile to delete: ");
    // scanf("%d", &idToDelete);
    if (isIdValid(&idToDelete) == -1)
    {
        return -1;
    }

    if (confirm() == -1)
    {
        return -1;
    }

    FILE *file = openFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return -1;
    }

    FILE *tempFile = openFile("./files/tempMobileData.bin", "wb");
    if (tempFile == NULL)
    {
        printf("\n\e[31mError: Unable to open tempMobileData.bin file.\e[m\n");
        escape();
        fclose(file);
        return -1;
    }

    MobileData mobile;
    while (readMobile(file, &mobile) == 1)
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

int isIdValid(int *id)
{
    printf("Enter the ID of the mobile to delete: ");
    getIntInput(id);
    // getchar();

    FILE *file = openFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return -1;
    }

    // printf("demo");
    int idFound;
    MobileData mobile;

    while (readMobile(file, &mobile) == 1)
    {
        if (mobile.id == *id && mobile.displayFlag == 2)
        {
            idFound = 1;
            break;
        }
    }

    fclose(file);

    if (idFound != 1)
    {
        printf("\n\e[31mInvalid ID.\e[m\n");
        // getchar();
        // escape();
        escape();
        return -1;
    }

    return 0;
}