#include "../../inc/common/utils.h"
#include "../../inc/buy/buy_top_sellers.h"
#include "../../inc/search/search_mobile.h"

int FilterByPrice()
{
    system("clear");
    InitDisplay();

    char input_name[50];
    char customer_name[50];
    int buy_quantity;
    float min_price, max_price;
    if (ViewByPriceRange(&min_price, &max_price) == -1)
        return FAILURE;
    if (IsBuy() == -1)
        return FAILURE;
    printf("\nEnter the name of the mobile to buy: ");
    scanf(" %49[^\n]s", input_name);

    FILE *file = OpenFile("../files/mobileData.bin", "rb+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    int mobile_found;
    MobileData_t mobile;

    while (ReadMobile(file, &mobile) == 1)
    {
        if (strcasecmp(mobile.name, input_name) == 0 && mobile.finalPrice >= min_price && mobile.finalPrice <= max_price && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            mobile_found = 1;
            break;
        }
    }
    if (mobile_found != 1)
    {
        fclose(file);
        printf("\n\e[31mInvalid Name.\e[m\n");
        Escape();
        return FAILURE;
    }

    AskCustomerDetails(customer_name, &buy_quantity);

    ProcessPurchase(&mobile, file, input_name, customer_name, buy_quantity);
}

int FilterByConfig()
{
    DisplayConfigMenu();
}

int DisplayConfigMenu()
{
    int choice;
    int config_count = 1;
    while (config_count <= 3)
    {
        system("clear");
        InitDisplay();
        printf("\n\e[1;36mConfiguration Menu:\e[m\n");
        printf("1. Filter by RAM\n");
        printf("2. Filter by Storage\n");
        printf("3. Filter by Chipset\n");
        printf("4. Filter by Camera\n");
        printf("5. Back\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        GetIntInput(&choice);

        switch (choice)
        {
        case 1:
            FilterByRAM();
            break;
        case 2:
            FilterByStorage();
            break;
        case 3:
            FilterByChipset();
            break;
        case 4:
            FilterByCamera();
            break;
        case 5:
            return SUCCESS;
            break;
        case 6:
            printf("\n\e[1;33mExiting Application ...\e[m\n");
            exit(0);
            break;
        default:
            if (config_count == 3)
            {
                printf("\n\e[31mToo many attempts\nExiting Application ...\e[m\n");
                exit(1);
            }
            printf("\n\e[31mInvalid choice. Please try again.\e[m\n");
            Escape();
            config_count++;
            break;
        }
    }
}

int ViewByPriceRange(float *min_price, float *max_price)
{
    MobileData_t mobile;
    int readResult;
    printf("Enter minimum price: ");
    GetFloatInput(min_price);

    printf("Enter maximum price: ");
    GetFloatInput(max_price);

    FILE *file = OpenFile("../files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }
    int foundMobiles = 0;
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && mobile.finalPrice >= *min_price && mobile.finalPrice <= *max_price && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            PrintMobileDetails(mobile);
            foundMobiles++;
        }
    } while (readResult == 1);
    if (MobileFound(foundMobiles) == -1)
        return FAILURE;
    return SUCCESS;
}

int FilterByRAM()
{
    int input_ram;
    char input_name[50];
    char customer_name[50];
    int buy_quantity;
    if (ViewByRam(&input_ram) == -1)
        return FAILURE;
    if (IsBuy() == -1)
        return FAILURE;
    printf("\nEnter the name of the mobile to buy: ");
    scanf(" %49[^\n]s", input_name);

    FILE *file = OpenFile("../files/mobileData.bin", "rb+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    int mobile_found;
    MobileData_t mobile;

    while (ReadMobile(file, &mobile) == 1)
    {
        if (strcasecmp(mobile.name, input_name) == 0 && mobile.config.ram == input_ram && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            mobile_found = 1;
            break;
        }
    }
    if (mobile_found != 1)
    {
        fclose(file);
        printf("\n\e[31mInvalid Name.\e[m\n");
        Escape();
        return FAILURE;
    }

    AskCustomerDetails(customer_name, &buy_quantity);

    ProcessPurchase(&mobile, file, input_name, customer_name, buy_quantity);
}

int ViewByRam(int *input_ram)
{
    MobileData_t mobile;
    int readResult;
    printf("Enter RAM (8,12): ");
    GetIntInput(input_ram);
    while (*input_ram != 8 && *input_ram != 12)
    {
        printf("Enter valid RAM!\n");
        printf("Enter RAM (8,12): ");
        GetIntInput(input_ram);
    }
    FILE *file = OpenFile("../files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }
    int foundMobiles = 0;
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && mobile.config.ram == *input_ram && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            PrintMobileDetails(mobile);
            foundMobiles++;
        }
    } while (readResult == 1);
    if (MobileFound(foundMobiles) == -1)
        return FAILURE;
    return SUCCESS;
}

int FilterByChipset()
{
    char input_chipset[50];
    char input_name[50];
    char customer_name[50];
    int buy_quantity;
    if (ViewByChipset(input_chipset) == -1)
        return FAILURE;
    if (IsBuy() == -1)
        return FAILURE;
    printf("\nEnter the name of the mobile to buy: ");
    scanf(" %49[^\n]s", input_name);

    FILE *file = OpenFile("../files/mobileData.bin", "rb+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    int mobile_found;
    MobileData_t mobile;

    while (ReadMobile(file, &mobile) == 1)
    {
        if (strcasecmp(mobile.name, input_name) == 0 && strcasecmp(mobile.config.chipset, input_chipset) == 0 && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            mobile_found = 1;
            break;
        }
    }
    if (mobile_found != 1)
    {
        fclose(file);
        printf("\n\e[31mInvalid Name.\e[m\n");
        Escape();
        return FAILURE;
    }

    AskCustomerDetails(customer_name, &buy_quantity);

    ProcessPurchase(&mobile, file, input_name, customer_name, buy_quantity);
}

int ViewByChipset(char *input_chipset)
{
    MobileData_t mobile;
    int readResult;

    printf("Enter Chipset (Snapdragon,Mediatec): ");
    scanf(" %49[^\n]", input_chipset);
    while (strcasecmp(input_chipset, "snapdragon") != 0 && strcasecmp(input_chipset, "Mediatec") != 0)
    {
        printf("Enter valid Chipset!\n");
        printf("Enter Chipset (Snapdragon,Mediatec): ");
        scanf(" %49[^\n]", input_chipset);
    }

    FILE *file = OpenFile("../files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }
    int foundMobiles = 0;
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && strcasecmp(input_chipset, mobile.config.chipset) == 0 && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            PrintMobileDetails(mobile);
            foundMobiles++;
        }
    } while (readResult == 1);
    if (MobileFound(foundMobiles) == -1)
        return FAILURE;
    return SUCCESS;
}

int FilterByCamera()
{
    int input_camera;
    char input_name[50];
    char customer_name[50];
    int buy_quantity;
    if (ViewByCamera(&input_camera) == -1)
        return FAILURE;
    if (IsBuy() == -1)
        return FAILURE;
    printf("\nEnter the name of the mobile to buy: ");
    scanf(" %49[^\n]s", input_name);

    FILE *file = OpenFile("../files/mobileData.bin", "rb+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    int mobile_found;
    MobileData_t mobile;

    while (ReadMobile(file, &mobile) == 1)
    {
        if (strcasecmp(mobile.name, input_name) == 0 && mobile.config.camera == input_camera && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            mobile_found = 1;
            break;
        }
    }
    if (mobile_found != 1)
    {
        fclose(file);
        printf("\n\e[31mInvalid Name.\e[m\n");
        Escape();
        return FAILURE;
    }

    AskCustomerDetails(customer_name, &buy_quantity);

    ProcessPurchase(&mobile, file, input_name, customer_name, buy_quantity);
}

int ViewByCamera(int *input_camera)
{
    MobileData_t mobile;
    int readResult;

    printf("Enter Camera (32,50,64): ");
    GetIntInput(input_camera);
    while (*input_camera != 32 && *input_camera != 50 && *input_camera != 64)
    {
        printf("Enter valid Camera!\n");
        printf("Enter Camera (32,50,64): ");
        GetIntInput(input_camera);
    }

    FILE *file = OpenFile("../files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }
    int foundMobiles = 0;
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && mobile.config.camera == *input_camera && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            PrintMobileDetails(mobile);
            foundMobiles++;
        }
    } while (readResult == 1);
    if (MobileFound(foundMobiles) == -1)
        return FAILURE;
    return SUCCESS;
}

int FilterByStorage()
{
    int input_storage;
    char input_name[50];
    char customer_name[50];
    int buy_quantity;
    if (ViewByStorage(&input_storage) == -1)
        return FAILURE;
    if (IsBuy() == -1)
        return FAILURE;
    printf("\nEnter the name of the mobile to buy: ");
    scanf(" %49[^\n]s", input_name);

    FILE *file = OpenFile("../files/mobileData.bin", "rb+");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }

    int mobile_found;
    MobileData_t mobile;

    while (ReadMobile(file, &mobile) == 1)
    {
        if (strcasecmp(mobile.name, input_name) == 0 && mobile.config.storage == input_storage && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            mobile_found = 1;
            break;
        }
    }
    if (mobile_found != 1)
    {
        fclose(file);
        printf("\n\e[31mInvalid Name.\e[m\n");
        Escape();
        return FAILURE;
    }

    AskCustomerDetails(customer_name, &buy_quantity);

    ProcessPurchase(&mobile, file, input_name, customer_name, buy_quantity);
}

int ViewByStorage(int *input_storage)
{
    MobileData_t mobile;
    int readResult;
    printf("Enter Storage (64,128,256): ");
    GetIntInput(input_storage);

    while (*input_storage != 64 && *input_storage != 128 && *input_storage != 256)
    {
        printf("Enter valid storage!\n");
        printf("Enter Storage (64,128,256): ");
        GetIntInput(input_storage);
    }
    FILE *file = OpenFile("../files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        Escape();
        return FAILURE;
    }
    int foundMobiles = 0;
    PrintHeader();
    do
    {
        readResult = ReadMobile(file, &mobile);
        if (readResult == 1 && mobile.config.storage == *input_storage && mobile.displayFlag != outdated && mobile.displayFlag != outOfStock)
        {
            PrintMobileDetails(mobile);
            foundMobiles++;
        }
    } while (readResult == 1);
    if (MobileFound(foundMobiles) == -1)
        return FAILURE;
    return SUCCESS;
}

int MobileFound(int foundMobiles)
{
    if (foundMobiles == 0)
    {
        printf("\n\e[31mNo matching mobiles found.\e[m\n");
        Escape();
        return FAILURE;
    }
    else
    {
        printf("\n\e[32m%d\e[m Mobiles Found.\n", foundMobiles);
        return 1;
    }
}
