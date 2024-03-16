#include "../../inc/includes.h"
#include "../../inc/struct.h"
#include "../../inc/addMobile.h"
#include "../../inc/utils.h"

void addMobile()
{
    askDetails();
}

int askDetails()
{
    char tempMobName[50];
    MobileData mobile;

    printf("Enter Mobile Name: ");
    scanf(" %49[^\n]", tempMobName);

    if (!checkIfMobileExists(tempMobName))
        return FAILURE;

    generateUniqueId(&mobile);

    strcpy(mobile.name, tempMobName);

    printf("Enter Brand Name: ");
    scanf(" %49[^\n]", mobile.brandName);

    printf("Enter Price: ");
    scanf(" %f", &mobile.price);

    printf("Enter Discount: ");
    scanf(" %f", &mobile.discount);

    mobile.finalPrice = mobile.price - (mobile.price * (mobile.discount / 100));

    printf("Enter Display Flag (0: New, 1: Refurbished, 2: Outdated, 3: Most Purchased, 4: Out of Stock): ");
    scanf(" %d", (int *)&mobile.displayFlag);

    printf("Enter Quantity: ");
    scanf(" %d", &mobile.quantity);

    mobile.count = 5;

    printf("Enter RAM: ");
    scanf(" %d", &mobile.config.ram);

    printf("Enter Storage: ");
    scanf(" %d", &mobile.config.storage);

    printf("Enter Chipset: ");
    scanf(" %49[^\n]", mobile.config.chipset);

    printf("Enter Camera: ");
    scanf(" %d", &mobile.config.camera);
    // printf("%p", &mobile);
    saveToDB(&mobile);

    // FILE *file = openFile("mobileData.bin", "a");
    // if (file == NULL)
    // {
    //     printf("Error: Unable to open mobileData.bin file.");
    //     return FAILURE;
    // }
    // fwrite(&mobile, sizeof(mobile), 1, file);
    // fclose(file);
}

int checkIfMobileExists(char *tempMobName)
{
    MobileData mobile;
    int readResult;
    FILE *file = openFile("../files/mobileData.bin", "ab+");
    if (file == NULL)
    {
        printf("Error: Unable to open mobileData.bin file.");
        return FAILURE;
    }

    do
    {
        readResult = readMobile(file, &mobile);
        if (readResult == 1 && strcmp(mobile.name, tempMobName) == 0)
        {
            fclose(file);
            printf("Mobile Already Exits!\n");
            // sleep(3);
            printf("Press Enter to continue...");
            getchar();
            getchar();

            return FAILURE;
        }
    } while (readResult == 1);

    fclose(file);
    return SUCCESS;
}

void generateUniqueId(MobileData *mobile)
{
    int tempId;
    FILE *file = openFile("../files/currentId.txt", "a+");
    if (file == NULL)
    {
        printf("\e[31mError: Unable to open currentId.txt file.\e[m");
        return;
    }
    fscanf(file, "%d", &mobile->id);
    fclose(file);

    file = openFile("../files/currentId.txt", "w");
    tempId = mobile->id + 1;
    fprintf(file, "%d", tempId);
    fclose(file);
}

int saveToDB(MobileData *mobile)
{
    // printf("%p", &mobile);
    FILE *file = openFile("../files/mobileData.bin", "a");
    if (file == NULL)
    {
        printf("Error: Unable to open mobileData.bin file.");
        return FAILURE;
    }
    fwrite(mobile, sizeof(MobileData), 1, file);
    fclose(file);
    printf("Mobile added successfully!\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
    // sleep(2);
    return SUCCESS;
}