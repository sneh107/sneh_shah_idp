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
    printf("\e[1m\e[34mWelcome to Phone-Dikhao\e[m\n");
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
        return SUCCESS; // Successful read
    }
    else if (feof(file))
    {
        return FAILURE; // End of file
    }
    else
    {
        printf("Error reading mobile from file.\n");
        return FAILURE; // Error
    }
}