// Shree Ganeshay Namah!

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/main.h"
#include "../inc/utils.h"

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
} MobileData;
void addMobile();
int askDetails();
int checkIfMobileExists(char *tempMobName);
int readMobile(FILE *file, MobileData *mobile);
FILE *openFile(char *fileName, char *mode);
int saveToDB(const MobileData *mobile);

int main()
{
    initDisplay();
    // login();
    displayMainMenu();
    return 0;
}

int login()
{
    char username[20];
    char password[20];
    int loginCount = 0;
    while (loginCount < 3)
    {
        printf("Enter Admin Username: ");
        scanf(" %[^\n]s", username);
        printf("Enter Admin Password: ");
        scanf(" %[^\n]s", password);

        if (validateCredentials(username, password))
        {
            printf("Invalid credentials. Please try again.\n");
            loginCount++;
        }
        else
        {
            printf("Login Successful!\n");
            return 0;
        }
    }
    printf("Too many attempts\nExiting Application ...\n");
    exit(1);
}
int validateCredentials(char *username, char *password)
{
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
        return 0;
    else
        return 1;
}

int displayMainMenu()
{
    int choice;

    printf("1. Add Mobile\n");
    printf("2. Delete Mobile\n");
    printf("3. Edit Mobile\n");
    printf("4. Search Mobile\n");
    printf("5. View Top Sellers\n");
    printf("6. Exit\n");

    int mainCount = 0;
    while (mainCount < 3)
    {
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addMobile();
            break;
        case 2:
            deleteMobile();
            break;
        case 3:
            editMobile();
            break;
        case 4:
            searchMobile();
            break;
        case 5:
            viewTopSellers();
            break;
        case 6:
            printf("Exiting Application ...\n");
            exit(0);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            mainCount++;
            break;
        }
    }
}

FILE *openFile(char *fileName, char *mode)
{
    FILE *file = fopen(fileName, mode);
    return file;
}

void addMobile()
{
    askDetails();
}

void generateUniqueId(MobileData *mobile)
{
    int tempId;
    FILE *file = openFile("../files/currentId.txt", "r");
    if (file == NULL)
    {
        printf("Error: Unable to open currentId.txt file.");
        return;
    }
    fscanf(file, "%d", &mobile->id);
    fclose(file);

    file = openFile("../files/currentId.txt", "w");
    tempId = mobile->id + 1;
    fprintf(file, "%d", tempId);
    fclose(file);
}

int askDetails()
{
    char tempMobName[50];
    MobileData mobile;
    int checkResult;

    // mobile.id = 3;

    printf("Enter Mobile Name: ");
    scanf(" %49[^\n]", tempMobName);

    checkResult = checkIfMobileExists(tempMobName);
    if (checkResult == 0)
    {
        printf("Mobile Already Exists!");
        return 0;
    }
    generateUniqueId(&mobile);

    strcpy(mobile.name, tempMobName);

    printf("Enter Brand Name: ");
    scanf(" %49[^\n]", mobile.brandName); // Read brand name

    printf("Enter Price: ");
    scanf(" %f", &mobile.price); // Read price

    printf("Enter Discount: ");
    scanf(" %f", &mobile.discount); // Read discount

    mobile.finalPrice = mobile.price - (mobile.price * (mobile.discount / 100));

    printf("Enter Display Flag (0: New, 1: Refurbished, 2: Outdated, 3: Most Purchased, 4: Out of Stock): ");
    scanf(" %d", &mobile.displayFlag); // Read display flag

    printf("Enter Quantity: ");
    scanf(" %d", &mobile.quantity); // Read quantity

    mobile.count = 5;

    printf("Enter RAM: ");
    scanf(" %d", &mobile.config.ram); // Read RAM

    printf("Enter Storage: ");
    scanf(" %d", &mobile.config.storage); // Read storage

    printf("Enter Chipset: ");
    scanf(" %49[^\n]", mobile.config.chipset); // Read chipset

    printf("Enter Camera: ");
    scanf(" %d", &mobile.config.camera);
    printf("%p", &mobile);
    saveToDB(&mobile);

    // FILE *file = openFile("mobileData.bin", "a");
    // if (file == NULL)
    // {
    //     printf("Error: Unable to open mobileData.bin file.");
    //     return 0;
    // }
    // fwrite(&mobile, sizeof(mobile), 1, file);
    // fclose(file);
}

int saveToDB(const MobileData *mobile)
{
    printf("%p", &mobile);
    FILE *file = openFile("mobileData.bin", "a");
    if (file == NULL)
    {
        printf("Error: Unable to open mobileData.bin file.");
        return 0;
    }
    fwrite(mobile, sizeof(MobileData), 1, file);
    fclose(file);
    printf("Mobile added successfully!");
    return 1;
}

int checkIfMobileExists(char *tempMobName)
{
    MobileData mobile;
    int readResult;
    FILE *file = openFile("mobileData.bin", "ab+"); // Open in read mode
    if (file == NULL)
    {
        printf("Error: Unable to open mobileData.bin file.");
        return 0;
    }

    do
    {
        readResult = readMobile(file, &mobile);
        if (readResult == 1 && strcmp(mobile.name, tempMobName) == 0)
        {
            fclose(file); // Close the file before returning
            return 0;     // Mobile found
        }
    } while (readResult == 1);

    fclose(file); // Close the file before returning
    return 1;     // Mobile not found
}
// MobileData *readMobile(FILE *file) {
//     MobileData mobile;
//     int readResult;
//     readResult = fread(&mobile, sizeof(MobileData), 1, file);
//     if (readResult == 1)
//         return &mobile;
//     else if (feof(file)) {
//         return NULL;
//     } else {
//         printf("Error reading mobile from file.");
//         return NULL;
//     }
// }

int readMobile(FILE *file, MobileData *mobile)
{
    int readResult = fread(mobile, sizeof(MobileData), 1, file);
    if (readResult == 1)
    {
        return 1; // Successful read
    }
    else if (feof(file))
    {
        return 0; // End of file
    }
    else
    {
        printf("Error reading mobile from file.\n");
        return -1; // Error
    }
}

int deleteMobile()
{
}
int editMobile()
{
}
int searchMobile()
{
}
int viewTopSellers()
{
}