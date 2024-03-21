//  * This file contains function prototypes for various utility functions used
//  * throughout the application. It includes functions for initializing display,
//  * printing asterisks, opening files, reading mobile data, confirming actions,
//  * printing headers, printing mobile details, and handling user input.

// /*******************************************************************************
//  * Copyright(c) 2024, Volansys Technologies
//  *
//  * Description:
//  * @file utils.h
//  * @brief Header file containing utility function declarations.
//  *
//  * This file contains function prototypes for various utility functions used
//  * throughout the application.
//  *
//  * Author       - Sneh Shah
//  *
//  *******************************************************************************
//  *
//  * History
//  *
//  * Mar/20/2024, Sneh Shah, Implemented utility functions for better user interaction
//  *
//  * Mar/18/2024, Sneh Shah, Created
//  *
//  ******************************************************************************/

// #ifndef UTILS_H
// #define UTILS_H

// /*******************
//  * Includes
//  *******************/
// #include "../includes.h"

// /*************************
//  * Defines
//  *************************/
// /* None */

// /**************************************
//  * Structures, Enumerations, Typedefs
//  *************************************/
// /* None */

// /***********************
//  * Global Variables
//  ***********************/
// /* None */

// /************************
//  * Function Prototypes
//  ************************/

// /**
//  * @brief Initializes the display settings.
//  *
//  * This function initializes the display settings, such as clearing the screen
//  * and setting up the terminal.
//  */
// void InitDisplay();

// /**
//  * @brief Prints asterisks to the console.
//  *
//  * This function prints a specified number of asterisks to the console.
//  *
//  * @param[in]   terminalWidth   Width of the terminal/console.
//  */
// void PrintAsterisk(int terminalWidth);

// /**
//  * @brief Prints left padding to the console.
//  *
//  * This function prints left padding to the console to align text properly.
//  *
//  * @param[in]   terminalWidth   Width of the terminal/console.
//  * @param[in]   strLen          Length of the string to be padded.
//  */
// void PrintLeftPadding(int terminalWidth, int strLen);

// /**
//  * @brief Opens a file.
//  *
//  * This function opens a file with the specified filename and mode.
//  *
//  * @param[in]   fileName    Name of the file to be opened.
//  * @param[in]   mode        Mode in which the file should be opened.
//  *
//  * @return Returns a pointer to the opened file, or NULL if an error occurs.
//  */
// FILE *OpenFile(char *fileName, char *mode);

// /**
//  * @brief Reads mobile data from a file.
//  *
//  * This function reads mobile data from a file and stores it in the provided structure.
//  *
//  * @param[in]   file    Pointer to the file from which data should be read.
//  * @param[out]  mobile  Pointer to the structure where the read data should be stored.
//  *
//  * @return Returns 0 upon success, -1 otherwise.
//  */
// int ReadMobile(FILE *file, MobileData_t *mobile);

// /**
//  * @brief Asks for user confirmation.
//  *
//  * This function asks the user for confirmation by prompting for a yes/no response.
//  *
//  * @return Returns 1 if the user confirms (yes), 0 otherwise (no).
//  */
// int Confirm();

// /**
//  * @brief Prints the header of a table.
//  *
//  * This function prints the header of a table with appropriate column headings.
//  */
// void PrintHeader();

// /**
//  * @brief Prints the details of a mobile.
//  *
//  * This function prints the details of a mobile to the console.
//  *
//  * @param[in]   mobile  The mobile whose details should be printed.
//  */
// void PrintMobileDetails(MobileData_t mobile);

// /**
//  * @brief Exits the program.
//  *
//  * This function exits the program gracefully.
//  */
// void Escape();

// /**
//  * @brief Exits the program.
//  *
//  * This function exits the program gracefully.
//  */
// void Escape1();

// /**
//  * @brief Gets integer input from the user.
//  *
//  * This function prompts the user to enter an integer and validates the input.
//  *
//  * @param[out]   num   Pointer to store the entered integer value.
//  *
//  * @return Returns 0 upon success, -1 otherwise.
//  */
// int GetIntInput(int *num);

// /**
//  * @brief Gets floating-point input from the user.
//  *
//  * This function prompts the user to enter a floating-point number and validates the input.
//  *
//  * @param[out]   num   Pointer to store the entered floating-point value.
//  *
//  * @return Returns 0 upon success, -1 otherwise.
//  */
// int GetFloatInput(float *num);

// #endif

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
int ReadMobile(FILE *file, MobileData_t *mobile);
int Confirm();
void PrintHeader();
void PrintMobileDetails(MobileData_t mobile);
void Escape();
void Escape1();
int GetIntInput(int *num);
int GetFloatInput(float *num);

#endif