#include "../../inc/includes.h"
#include "../../inc/struct.h"
#include "../../inc/utils.h"

void initDisplay()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int terminalWidth = w.ws_col;

    // system("clear");
    asterisk(terminalWidth);
    printLeftPadding(terminalWidth, 23);
    printf("\e[1;34mWelcome to Phone-Dikhao\e[m\n");
    // printf("\e[1m\e[34mWelcome to Phone-Dikhao\e[m\n");
    printLeftPadding(terminalWidth, 28);
    printf("\e[34mA mobile showcasing platform\e[m\n");
    asterisk(terminalWidth);
}

void asterisk(int terminalWidth)
{
    for (int i = 0; i < terminalWidth; i++)
    {
        printf("\e[32m*\e[m");
    }
    printf("\n");
}

void printLeftPadding(int terminalWidth, int strLen)
{
    int padding = (terminalWidth - strLen) / 2;
    for (int i = 0; i < padding; i++)
    {
        printf(" ");
    }
}

FILE *openFile(char *fileName, char *mode)
{
    FILE *file = fopen(fileName, mode);
    return file;
}

int readMobile(FILE *file, MobileData *mobile)
{
    int readResult = fread(mobile, sizeof(MobileData), 1, file);
    if (readResult == 1)
    {
        return SUCCESS;
    }
    else if (feof(file))
    {
        return FAILURE;
    }
    else
    {
        printf("\n\e[31mError reading mobile from file.\e[m\n");
        escape();
        return FAILURE;
    }
}

int isIdValid(int *id)
{
    printf("Enter the ID of the mobile to delete: ");
    getIntInput(id);

    FILE *file = openFile("./files/mobileData.bin", "rb");
    if (file == NULL)
    {
        printf("\n\e[31mError: Unable to open mobileData.bin file.\e[m\n");
        escape();
        return FAILURE;
    }

    int idFound = 0;
    MobileData mobile;

    while (readMobile(file, &mobile))
    {
        if (mobile.id == *id)
        {
            idFound = 1;
            break;
        }
    }

    fclose(file);

    if (!idFound)
    {
        printf("\n\e[31mInvalid ID.\e[m\n");
        escape();
        return FAILURE;
    }

    return SUCCESS;
}

int confirm()
{
    char confirmation;
    printf("Confirm? \e[1;33m(y/n):\e[m ");
    scanf(" %c", &confirmation);

    if (confirmation == 'n' || confirmation == 'N')
    {

        printf("\n\e[31mOperation cancelled.\e[m\n");
        escape();
        return FAILURE;
    }
    else if (confirmation == 'y' || confirmation == 'Y')
    {
        return SUCCESS;
    }
    else
    {
        printf("\n\e[31mInvalid Input!\e[m\n");
        escape();
        return FAILURE;
    }
}

void printHeader()
{
    printf("%-3s %-20s %-10s %-10s %-10s %-10s %-4s %-8s %-5s %-4s %-7s %-15s %-6s\n", "MID", "Name", "BrandName", "Price", "Discount", "FinalPrice", "Flag", "Quantity", "Count", "RAM", "Storage", "Chipset", "Camera");
}

void printMobileDetails(MobileData mobile)
{
    printf("%-3d %-20s %-10s %-10.2f %-10.2f %-10.2f %-4d %-8d %-5d %-4d %-7d %-15s %-6d\n", mobile.id, mobile.name, mobile.brandName, mobile.price, mobile.discount, mobile.finalPrice, mobile.displayFlag, mobile.quantity, mobile.count, mobile.config.ram, mobile.config.storage, mobile.config.chipset, mobile.config.camera);
}

void escape()
{
    printf("\nPress \e[1;33mEnter\e[m to continue...\n");
    getchar();
    getchar();
}
int getIntInput(int *num)
{
    while (scanf(" %d", num) != 1)
    {
        printf("Invalid input. Enter an integer: ");
        // Clear the input buffer
        while (getchar() != '\n')
            ;
    }
}
int getFloatInput(float *num)
{
    while (scanf("%f", num) != 1)
    {
        printf("Invalid input. Enter a floating-point number: ");
        // Clear the input buffer
        while (getchar() != '\n')
            ;
    }
}