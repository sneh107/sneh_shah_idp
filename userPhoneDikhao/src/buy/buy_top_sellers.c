// #include "../../inc/includes.h"
#include "../../inc/main.h"
#include "../../inc/common/utils.h"
#include "../../inc/buy/buy_top_sellers.h"

int BuyTopSellers()
{
    char input_name[50];
    char customer_name[50];
    int buy_quantity;
    ViewTopSellers();
    if (IsBuy() == -1)
        return -1;
    printf("Enter the name of the mobile to buy: ");
    scanf(" %49[^\n]s", input_name);
    // while (getchar() != '\n')
    //     ;

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
        if (strcasecmp(mobile.name, input_name) == 0 && mobile.displayFlag == mostPurchased)
        {
            mobile_found = 1;
            break;
        }
    }

    // fclose(file);

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

// int IsBuy()
// {
//     char confirmation;
//     printf("Want to Buy? \e[1;33m(y/n):\e[m ");
//     scanf(" %c", &confirmation);

//     if (confirmation == 'n' || confirmation == 'N')
//     {

//         printf("\n\e[31mOperation cancelled.\e[m\n");
//         Escape();
//         return FAILURE;
//     }
//     else if (confirmation == 'y' || confirmation == 'Y')
//     {
//         return SUCCESS;
//     }
//     else
//     {
//         printf("\n\e[31mInvalid Input!\e[m\n");
//         Escape();
//         return FAILURE;
//     }
// }

// int Confirm()
// {
//     char confirmation;
//     printf("Confirm? \e[1;33m(y/n):\e[m ");
//     scanf(" %c", &confirmation);
//     while (getchar() != '\n')
//         ;

//     if (confirmation == 'n' || confirmation == 'N')
//     {

//         printf("\n\e[31mOperation cancelled.\e[m\n");
//         Escape();
//         return FAILURE;
//     }
//     else if (confirmation == 'y' || confirmation == 'Y')
//     {
//         return SUCCESS;
//     }
//     else
//     {
//         printf("\n\e[31mInvalid Input!\e[m\n");
//         Escape();
//         return FAILURE;
//     }
// }

// void AskCustomerDetails(char *customer_name, int *buy_quantity)
// {
//     printf("Enter Your Name: ");
//     scanf(" %49[^\n]s", customer_name);

//     printf("Enter Quantity to Purchase: ");
//     scanf(" %d", buy_quantity);
// }