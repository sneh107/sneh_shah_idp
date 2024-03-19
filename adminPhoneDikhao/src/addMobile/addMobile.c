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

    if (checkIfMobileExists(tempMobName) != SUCCESS)
    {
        return FAILURE;
    }

    generateUniqueId(&mobile);

    strcpy(mobile.name, tempMobName);

    printf("Enter Brand Name: ");
    scanf(" %49[^\n]", mobile.brandName);

    printf("Enter Price: ");
    getFloatInput(&mobile.price);
    while (mobile.price <= 0 || mobile.price >= 200000)
    // if (mobile.price <= 0 || mobile.price >= 200000)
    {
        printf("Enter valid price!\n");
        printf("Enter Price: ");
        getFloatInput(&mobile.price);
    }

    printf("Enter Discount(in percentage): ");
    getFloatInput(&mobile.discount);
    while (mobile.discount <= 0)
    // if (mobile.discount <= 0)
    {
        printf("Enter valid Discount!\n");
        printf("Enter Discount(in percentage): ");
        getFloatInput(&mobile.discount);
    }

    mobile.finalPrice = mobile.price - (mobile.price * (mobile.discount / 100));

    printf("Enter Display Flag (0: New, 1: Refurbished): ");
    getIntInput((int *)&mobile.displayFlag);
    while (mobile.displayFlag != 0 && mobile.displayFlag != 1)
    // if (mobile.displayFlag != 0 && mobile.displayFlag != 1)
    {
        printf("Enter valid display flag!\n");
        printf("Enter Display Flag (0: New, 1: Refurbished): ");
        getIntInput((int *)&mobile.displayFlag);
    }

    printf("Enter Quantity: ");
    // scanf(" %d", &mobile.quantity);
    getIntInput(&mobile.quantity);
    while (mobile.quantity <= 0)
    // if (mobile.quantity <= 0)
    {
        printf("Enter valid Quantity!\n");
        printf("Enter Quantity: ");
        getIntInput(&mobile.quantity);
    }

    mobile.count = 0;

    printf("Enter RAM (8,12): ");
    // scanf(" %d", &mobile.config.ram);
    getIntInput(&mobile.config.ram);
    while (mobile.config.ram != 8 && mobile.config.ram != 12)
    // if (mobile.config.ram != 8 && mobile.config.ram != 12)
    {
        printf("Enter valid RAM!\n");
        printf("Enter RAM (8,12): ");
        getIntInput(&mobile.config.ram);
    }

    printf("Enter Storage (64,128,256): ");
    // scanf(" %d", &mobile.config.storage);
    getIntInput(&mobile.config.storage);
    while (mobile.config.storage != 64 && mobile.config.storage != 128 && mobile.config.storage != 256)
    // if (mobile.config.storage != 64 && mobile.config.storage != 128 && mobile.config.storage != 256)
    {
        printf("Enter valid storage!\n");
        printf("Enter Storage (64,128,256): ");
        getIntInput(&mobile.config.storage);
    }

    printf("Enter Chipset (Snapdragon,Mediatec): ");
    scanf(" %49[^\n]", mobile.config.chipset);
    while (strcasecmp(mobile.config.chipset, "snapdragon") != 0 && strcasecmp(mobile.config.chipset, "Mediatec") != 0)
    // if (strcasecmp(mobile.config.chipset, "snapdragon") != 0 && strcasecmp(mobile.config.chipset, "Mediatec") != 0)
    {
        printf("Enter valid Chipset!\n");
        printf("Enter Chipset (Snapdragon,Mediatec): ");
        scanf(" %49[^\n]", mobile.config.chipset);
    }

    printf("Enter Camera (32,50,64): ");
    // scanf(" %d", &mobile.config.camera);
    getIntInput(&mobile.config.camera);
    while (mobile.config.camera != 32 && mobile.config.camera != 50 && mobile.config.camera != 64)
    // if (mobile.config.camera != 32 && mobile.config.camera != 50 && mobile.config.camera != 64)
    {
        printf("Enter valid Camera!\n");
        printf("Enter Camera (32,50,64): ");
        getIntInput(&mobile.config.camera);
    }
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
    FILE *file = openFile("./files/mobileData.bin", "ab+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return FAILURE;
    }

    do
    {
        readResult = readMobile(file, &mobile);
        if (readResult == 1 && strcasecmp(mobile.name, tempMobName) == 0)
        {
            fclose(file);
            printf("\n\e[31mMobile Already Exits!\e[m\n");
            // sleep(3);
            escape();

            return FAILURE;
        }
    } while (readResult == 1);

    fclose(file);
    return SUCCESS;
}

void generateUniqueId(MobileData *mobile)
{
    int tempId;
    FILE *file = openFile("./files/currentId.txt", "a+");
    // FILE *file = openFile("/home/sneh/Desktop/_test-PhoneDikhao/files/currentId.txt","a+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open currentId.txt file.\e[m\n");
        escape();
        return;
    }
    fscanf(file, "%d", &mobile->id);
    fclose(file);

    file = openFile("./files/currentId.txt", "w");
    tempId = mobile->id + 1;
    fprintf(file, "%d", tempId);
    fclose(file);
}

int saveToDB(MobileData *mobile)
{
    // printf("%p", &mobile);
    FILE *file = openFile("./files/mobileData.bin", "a");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return FAILURE;
    }
    fwrite(mobile, sizeof(MobileData), 1, file);
    fclose(file);
    printf("\n\e[32mMobile added successfully!\e[m\n");
    escape();
    // sleep(2);
    return SUCCESS;
}
