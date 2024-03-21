#include "../../inc/common/utils.h"
#include "../../inc/search/search_mobile.h"

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
        printf("\nConfiguration Menu:\n");
        printf("1. Filter by RAM\n");
        printf("2. Filter by Storage\n");
        printf("3. Filter by Chipset\n");
        printf("4. Filter by Camera\n");
        printf("5. Back\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

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

int FilterByPrice()
{
    char input_name[50];
    char customer_name[50];
    int buy_quantity;
    float min_price, max_price;
    ViewByPriceRange(&min_price, &max_price);
    if (IsBuy() == -1)
        return -1;
    printf("Enter the name of the mobile to buy: ");
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
        // getchar();
        // Escape();
        Escape();
        return FAILURE;
    }

    AskCustomerDetails(customer_name, &buy_quantity);

    if (buy_quantity > mobile.quantity)
    {
        fclose(file);
        printf("Not Enough Quantity!\n");
        Escape();
        return FAILURE;
    }

    // printf("Your name is : %s\n", customer_name);
    // printf("Your quan is : %d\n", buy_quantity);

    if (Confirm() == -1)
    {
        fclose(file);
        return FAILURE;
    }

    mobile.count = mobile.count + buy_quantity;
    if (mobile.count >= 5)
    {
        mobile.displayFlag = mostPurchased;
    }
    mobile.quantity = mobile.quantity - buy_quantity;
    if (mobile.quantity == 0)
    {
        mobile.displayFlag = outOfStock;
    }

    fseek(file, -sizeof(MobileData_t), SEEK_CUR);

    fwrite(&mobile, sizeof(MobileData_t), 1, file);

    fclose(file);

    file = OpenFile("../files/customer_data.txt", "a");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open customer_data.txt file.\e[m\n");
        Escape();
        return FAILURE;
    }

    // fprintf(file, "%-20s %-20s %-20s\n", "customer_name", "Mobile_name", "Quantity_Purchased");
    fprintf(file, "%-20s %-20s %-20d\n", customer_name, input_name, buy_quantity);

    fclose(file);
    printf("Mobile Bought Succeessfully");
    Escape();
    return SUCCESS;
}

int ViewByPriceRange(float *min_price, float *max_price)
{
    MobileData_t mobile;
    int readResult;
    printf("Enter minimum price: ");
    scanf(" %f", min_price);

    printf("Enter maximum price: ");
    scanf(" %f", max_price);

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
    MobileFound(foundMobiles);
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
        return -1;
    printf("Enter the name of the mobile to buy: ");
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
        // getchar();
        // Escape();
        Escape();
        return FAILURE;
    }

    AskCustomerDetails(customer_name, &buy_quantity);

    if (buy_quantity > mobile.quantity)
    {
        fclose(file);
        printf("Not Enough Quantity!\n");
        Escape();
        return FAILURE;
    }

    // printf("Your name is : %s\n", customer_name);
    // printf("Your quan is : %d\n", buy_quantity);

    if (Confirm() == -1)
    {
        fclose(file);
        return FAILURE;
    }

    mobile.count = mobile.count + buy_quantity;
    if (mobile.count >= 5)
    {
        mobile.displayFlag = mostPurchased;
    }
    mobile.quantity = mobile.quantity - buy_quantity;
    if (mobile.quantity == 0)
    {
        mobile.displayFlag = outOfStock;
    }

    fseek(file, -sizeof(MobileData_t), SEEK_CUR);

    fwrite(&mobile, sizeof(MobileData_t), 1, file);

    fclose(file);

    file = OpenFile("../files/customer_data.txt", "a");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open customer_data.txt file.\e[m\n");
        Escape();
        return FAILURE;
    }

    // fprintf(file, "%-20s %-20s %-20s\n", "customer_name", "Mobile_name", "Quantity_Purchased");
    fprintf(file, "%-20s %-20s %-20d\n", customer_name, input_name, buy_quantity);

    fclose(file);
    printf("Mobile Bought Succeessfully");
    Escape();
    return SUCCESS;
}

int ViewByStorage(int *input_storage)
{
    MobileData_t mobile;
    int readResult;
    printf("Enter Storage (64,128,256): ");
    scanf(" %d", input_storage);

    while (*input_storage != 64 && *input_storage != 128 && *input_storage != 256)
    {
        printf("Enter valid storage!\n");
        printf("Enter Storage (64,128,256): ");
        scanf(" %d", input_storage);
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

int FilterByRAM()
{
    int input_ram;
    char input_name[50];
    char customer_name[50];
    int buy_quantity;
    ViewByRam(&input_ram);
    if (IsBuy() == -1)
        return -1;
    printf("Enter the name of the mobile to buy: ");
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
        // getchar();
        // Escape();
        Escape();
        return FAILURE;
    }

    AskCustomerDetails(customer_name, &buy_quantity);

    if (buy_quantity > mobile.quantity)
    {
        fclose(file);
        printf("Not Enough Quantity!\n");
        Escape();
        return FAILURE;
    }

    // printf("Your name is : %s\n", customer_name);
    // printf("Your quan is : %d\n", buy_quantity);

    if (Confirm() == -1)
    {
        fclose(file);
        return FAILURE;
    }

    mobile.count = mobile.count + buy_quantity;
    if (mobile.count >= 5)
    {
        mobile.displayFlag = mostPurchased;
    }
    mobile.quantity = mobile.quantity - buy_quantity;
    if (mobile.quantity == 0)
    {
        mobile.displayFlag = outOfStock;
    }

    fseek(file, -sizeof(MobileData_t), SEEK_CUR);

    fwrite(&mobile, sizeof(MobileData_t), 1, file);

    fclose(file);

    file = OpenFile("../files/customer_data.txt", "a");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open customer_data.txt file.\e[m\n");
        Escape();
        return FAILURE;
    }

    // fprintf(file, "%-20s %-20s %-20s\n", "customer_name", "Mobile_name", "Quantity_Purchased");
    fprintf(file, "%-20s %-20s %-20d\n", customer_name, input_name, buy_quantity);

    fclose(file);
    printf("Mobile Bought Succeessfully");
    Escape();
    return SUCCESS;
}

int ViewByRam(int *input_ram)
{
    MobileData_t mobile;
    int readResult;
    printf("Enter RAM (8,12): ");
    scanf(" %d", input_ram);
    while (*input_ram != 8 && *input_ram != 12)
    // if (mobile.config.ram != 8 && mobile.config.ram != 12)
    {
        printf("Enter valid RAM!\n");
        printf("Enter RAM (8,12): ");
        scanf(" %d", input_ram);
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
    MobileFound(foundMobiles);
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
        // Escape();
    }
}

int FilterByChipset()
{
}

int FilterByCamera()
{
}