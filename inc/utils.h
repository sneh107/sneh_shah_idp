void initDisplay();
void asterisk(int terminalWidth);
void printLeftPadding(int terminalWidth, int strLen);
FILE *openFile(char *fileName, char *mode);
int readMobile(FILE *file, MobileData *mobile);

enum exitStatus
{
    FAILURE,
    SUCCESS
};