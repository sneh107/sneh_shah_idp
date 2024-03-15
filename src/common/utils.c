#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../../inc/utils.h"
#include <stdlib.h>

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