#include "../../inc/includes.h"
#include "../../inc/common/utils.h"

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
        return 1;
    }
    else if (feof(file))
    {
        return -1;
    }
    else
    {
        printf("\n\e[31mError reading mobile from file.\e[m\n");
        escape();
        return -1;
    }
}

int confirm()
{
    char confirmation;
    printf("Confirm? \e[1;33m(y/n):\e[m ");
    scanf(" %c", &confirmation);
    while (getchar() != '\n')
        ;

    if (confirmation == 'n' || confirmation == 'N')
    {

        printf("\n\e[31mOperation cancelled.\e[m\n");
        escape();
        return -1;
    }
    else if (confirmation == 'y' || confirmation == 'Y')
    {
        return 0;
    }
    else
    {
        printf("\n\e[31mInvalid Input!\e[m\n");
        escape();
        return -1;
    }
}

void printHeader()
{
    printf("%-3s %-20s %-10s %-10s %-12s %-10s %-15s %-8s %-5s %-8s %-12s %-15s %-6s\n", "MID", "Name", "BrandName", "Price", "Discount(%)", "FinalPrice", "Flag", "Quantity", "Count", "RAM(Gb)", "Storage(GB)", "Chipset", "Camera(MP)");
}

void printMobileDetails(MobileData mobile)
{
    char flag[50];

    switch (mobile.displayFlag)
    {
    case new:
        strcpy(flag, "New");
        break;
    case refurbished:
        strcpy(flag, "Refurbished");
        break;
    case outdated:
        strcpy(flag, "Outdated");
        break;
    case mostPurchased:
        strcpy(flag, "Most Purchased");
        break;
    case outOfStock:
        strcpy(flag, "Out of Stock");
        break;
    default:
        break;
    }

    printf("%-3d %-20s %-10s %-10.2f %-12.2f %-10.2f %-15s %-8d %-5d %-8d %-12d %-15s %-6d\n", mobile.id, mobile.name, mobile.brandName, mobile.price, mobile.discount, mobile.finalPrice, flag, mobile.quantity, mobile.count, mobile.config.ram, mobile.config.storage, mobile.config.chipset, mobile.config.camera);
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
        printf("Invalid input. Enter a number: ");
        // Clear the input buffer
        while (getchar() != '\n')
            ;
    }
}
int getFloatInput(float *num)
{
    while (scanf("%f", num) != 1)
    {
        printf("Invalid input. Enter a number: ");
        // Clear the input buffer
        while (getchar() != '\n')
            ;
    }
}