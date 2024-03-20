// #include "../../inc/includes.h"
#include "../../inc/common/utils.h"
#include "../../inc/deleteMobile/deleteMobile.h"

int DeleteMobile()
{
    DisplayOutdatedMobiles();

    int idToDelete;
    // printf("Enter the ID of the mobile to delete: ");
    // scanf("%d", &idToDelete);
    if (IsIdValid(&idToDelete) == -1)
    {
        return FAILURE;
    }

    if (Confirm() == -1)
    {
        return FAILURE;
    }

    FILE *file = OpenFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    FILE *tempFile = OpenFile("./files/tempmobileData.bin", "wb");
    if (tempFile == NULL)
    {
        printf("\n\e[31mError: Unable to open tempmobileData.bin file.\e[m\n");
        Escape();
        fclose(file);
        return FAILURE;
    }

    MobileData_t mobile;
    while (ReadMobile(file, &mobile) == 1)
    {
        if (mobile.id != idToDelete)
        {
            fwrite(&mobile, sizeof(MobileData_t), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("./files/mobileData.bin");
    rename("./files/tempmobileData.bin", "./files/mobileData.bin");

    printf("\n\e[32mMobile record with ID %d deleted successfully.\e[m\n", idToDelete);
    Escape1();
}

void DisplayOutdatedMobiles()
{
    MobileData_t mobile;
    int readResult;
    FILE *file = OpenFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return;
    }
    printf("\n");
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && mobile.displayFlag == 2)
        {
            PrintMobileDetails(mobile);
        }
    } while (readResult == 1);
    printf("\n");

    fclose(file);
    // Escape();
}

int IsIdValid(int *id)
{
    printf("Enter the ID of the mobile to delete: ");
    GetIntInput(id);
    // getchar();

    FILE *file = OpenFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    // printf("demo");
    int idFound;
    MobileData_t mobile;

    while (ReadMobile(file, &mobile) == 1)
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
        // Escape();
        Escape();
        return FAILURE;
    }

    return SUCCESS;
}