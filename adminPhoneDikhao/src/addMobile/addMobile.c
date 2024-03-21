// #include "../../inc/includes.h"
#include "../../inc/addMobile/addMobile.h"
#include "../../inc/common/utils.h"

int AddMobile()
{
    char tempMobName[50];
    MobileData_t mobile;

    printf("Enter Mobile Name: ");
    scanf(" %49[^\n]", tempMobName);

    if (CheckIfMobileExists(tempMobName) != 0)
    {
        return FAILURE;
    }

    GenerateUniqueId(&mobile);

    strcpy(mobile.name, tempMobName);

    printf("Enter Brand Name: ");
    scanf(" %49[^\n]", mobile.brandName);

    printf("Enter Price: ");
    GetFloatInput(&mobile.price);
    while (mobile.price <= 0 || mobile.price >= 200000)
    // if (mobile.price <= 0 || mobile.price >= 200000)
    {
        printf("Enter valid price!\n");
        printf("Enter Price: ");
        GetFloatInput(&mobile.price);
    }

    printf("Enter Discount(in percentage): ");
    GetFloatInput(&mobile.discount);
    while (mobile.discount <= 0)
    // if (mobile.discount <= 0)
    {
        printf("Enter valid Discount!\n");
        printf("Enter Discount(in percentage): ");
        GetFloatInput(&mobile.discount);
    }

    mobile.finalPrice = mobile.price - (mobile.price * (mobile.discount / 100));

    printf("Enter Display Flag (0: New, 1: Refurbished): ");
    GetIntInput((int *)&mobile.displayFlag);
    while (mobile.displayFlag != 0 && mobile.displayFlag != 1)
    // if (mobile.displayFlag != 0 && mobile.displayFlag != 1)
    {
        printf("Enter valid display flag!\n");
        printf("Enter Display Flag (0: New, 1: Refurbished): ");
        GetIntInput((int *)&mobile.displayFlag);
    }

    printf("Enter Quantity: ");
    // scanf(" %d", &mobile.quantity);
    GetIntInput(&mobile.quantity);
    while (mobile.quantity <= 0)
    // if (mobile.quantity <= 0)
    {
        printf("Enter valid Quantity!\n");
        printf("Enter Quantity: ");
        GetIntInput(&mobile.quantity);
    }

    mobile.count = 0;

    printf("Enter RAM (8,12): ");
    // scanf(" %d", &mobile.config.ram);
    GetIntInput(&mobile.config.ram);
    while (mobile.config.ram != 8 && mobile.config.ram != 12)
    // if (mobile.config.ram != 8 && mobile.config.ram != 12)
    {
        printf("Enter valid RAM!\n");
        printf("Enter RAM (8,12): ");
        GetIntInput(&mobile.config.ram);
    }

    printf("Enter Storage (64,128,256): ");
    // scanf(" %d", &mobile.config.storage);
    GetIntInput(&mobile.config.storage);
    while (mobile.config.storage != 64 && mobile.config.storage != 128 && mobile.config.storage != 256)
    // if (mobile.config.storage != 64 && mobile.config.storage != 128 && mobile.config.storage != 256)
    {
        printf("Enter valid storage!\n");
        printf("Enter Storage (64,128,256): ");
        GetIntInput(&mobile.config.storage);
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
    GetIntInput(&mobile.config.camera);
    while (mobile.config.camera != 32 && mobile.config.camera != 50 && mobile.config.camera != 64)
    // if (mobile.config.camera != 32 && mobile.config.camera != 50 && mobile.config.camera != 64)
    {
        printf("Enter valid Camera!\n");
        printf("Enter Camera (32,50,64): ");
        GetIntInput(&mobile.config.camera);
    }
    // printf("%p", &mobile);
    SaveToDB(&mobile);

    // FILE *file = OpenFile("mobileData.bin", "a");
    // if (file == NULL)
    // {
    //     printf("Error: Unable to open mobileData.bin file.");
    //     return FAILURE;
    // }
    // fwrite(&mobile, sizeof(mobile), 1, file);
    // fclose(file);
    return SUCCESS;
}

int CheckIfMobileExists(char *tempMobName)
{
    MobileData_t mobile;
    int readResult;
    FILE *file = OpenFile("../files/mobileData.bin", "ab+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && strcasecmp(mobile.name, tempMobName) == 0)
        {
            fclose(file);
            printf("\n\e[31mMobile Already Exits!\e[m\n");
            // sleep(3);
            Escape();

            return FAILURE;
        }
    } while (readResult == 1);

    fclose(file);
    return SUCCESS;
}

void GenerateUniqueId(MobileData_t *mobile)
{
    int tempId;
    FILE *file = OpenFile("../files/currentId.txt", "a+");
    // FILE *file = OpenFile("/home/sneh/Desktop/_test-PhoneDikhao/files/currentId.txt","a+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open currentId.txt file.\e[m\n");
        Escape();
        return;
    }
    fscanf(file, "%d", &mobile->id);
    fclose(file);

    file = OpenFile("../files/currentId.txt", "w");
    tempId = mobile->id + 1;
    fprintf(file, "%d", tempId);
    fclose(file);
}

int SaveToDB(MobileData_t *mobile)
{
    // printf("%p", &mobile);
    FILE *file = OpenFile("../files/mobileData.bin", "a");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }
    fwrite(mobile, sizeof(MobileData_t), 1, file);
    fclose(file);
    printf("\n\e[32mMobile added successfully!\e[m\n");
    Escape();
    // sleep(2);
    return SUCCESS;
}
