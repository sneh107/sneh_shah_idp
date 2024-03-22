#ifndef UTILS_H
#define UTILS_H

#include "../includes.h"

typedef enum
{
    FAILURE = -1,
    SUCCESS
} exitStatus_e;

void InitDisplay();
void PrintAsterisk(int terminalWidth);
void PrintLeftPadding(int terminalWidth, int strLen);
FILE *OpenFile(char *fileName, char *mode);
void Escape();
int ReadMobile(FILE *file, MobileData_t *mobile);
void PrintHeader();
void PrintMobileDetails(MobileData_t mobile);
int IsBuy();
int Confirm();
void AskCustomerDetails(char *customer_name, int *buy_quantity);
int GetIntInput(int *num);
int GetFloatInput(float *num);

#endif