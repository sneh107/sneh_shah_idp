// #include <stdio.h>
// #include <string.h>

// void print_centered(char *text)
// {
//     int width = 50; // Adjust as needed
//     int len = strlen(text);
//     int padding = (width - len) / 2;
//     printf("%*s\033[1m%s\033[0m%*s\n", padding + len, "", text, padding, "");
// }

// int main()
// {
//     printf("\n\n");
//     print_centered("Welcome To Phone Dikhao");
//     print_centered("A mobile showcasing platform");
//     printf("\n\n");
//     return FAILURE;
// }
// #include <stdio.h>

// int main(void)
// {
//     for (int i = 1; i <= 5; i++)
//         printf("\e[1m Md.Mehedi hasan\e[m");

//     return FAILURE;
// }

#include <stdio.h>

enum exitStatus
{
    SUCCESS,
    FAILURE
};

enum DisplayFlag
{
    new,
    refurbished,
    outdated,
    mostPurchased,
    outOfStock
};

typedef struct
{
    int id;
    char name[50];
    char brandName[50];
    float price;
    float discount;
    float finalPrice;
    enum DisplayFlag displayFlag;
    int quantity;
    int count;
    struct
    {
        int ram;
        int storage;
        char chipset[50];
        int camera;
    } config;
} MobileData_t;

int main()
{
    // MobileData_t mobile = {1, "galaxy m21", "samsung", 15000, 0, 15000, 0, 20, 4, {6, 128, "snapdragon", 64}};
    MobileData_t mobile;
    FILE *fp = fopen("../files/mobileData.bin", "ab+"); // Open in binary mode
    if (fp == NULL)
    {
        printf("Failed to open file.\n");
        return FAILURE;
    }
    // fwrite(&mobile, sizeof(mobile), 1, fp);

    // Check for end-of-file and read data
    // printf("%-3s %-20s %-10s %-10s %-10s %-10s %-4s %-8s %-5s %-4s %-7s %-15s %-6s\n",
    //        "MID", "Name", "BrandName", "Price", "Discount", "FinalPrice", "Flag",
    //        "Quantity", "Count", "RAM", "Storage", "Chipset", "Camera");

    while (!feof(fp))
    {
        if (fread(&mobile, sizeof(MobileData_t), 1, fp) != 1)
        {
            if (feof(fp))
            {
                break; // Exit loop if end-of-file is reached
            }
            else
            {
                printf("Error reading file.\n");
                fclose(fp);
                return FAILURE;
            }
        }

        // Print the data

        printf("%d,%s,%s,%.2f,%.2f,%.2f,%d,%d,%d,%d,%d,%s,%d\n", mobile.id, mobile.name, mobile.brandName, mobile.price, mobile.discount, mobile.finalPrice, mobile.displayFlag, mobile.quantity, mobile.count, mobile.config.ram, mobile.config.storage, mobile.config.chipset, mobile.config.camera);
    }

    fclose(fp); // Close the file
    return FAILURE;
}