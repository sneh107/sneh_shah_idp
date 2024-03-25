/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file utils.h
 * @brief Header file containing utility function prototypes.
 *
 * This file contains function prototypes for utility functions used in the
 * application, such as file operations, input validation, and display functions.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Mar/20/2024, Sneh Shah, Created
 *
 ******************************************************************************/
#ifndef UTILS_H
#define UTILS_H
/*******************
 * Includes
 *******************/
#include "../includes.h"

/*************************
 * Defines
 *************************/
/* None */

/**************************************
 * Structures, Enumerations, Typedefs
 *************************************/
typedef enum
{
    FAILURE = -1,
    SUCCESS
} exitStatus_e;

/***********************
 * Global Variables
 ***********************/
/* None */

/************************
 * Function Prototypes
 ************************/

/**
 * @brief Initializes the display for the Phone-Dikhao application.
 *
 * This function initializes the display by printing a welcome message and decorative asterisks.
 * It also determines the terminal width to adjust the display accordingly.
 */
void InitDisplay();

/**
 * @brief Prints a line of asterisks to the terminal.
 *
 * This function prints a line of asterisks to the terminal with the specified width.
 *
 * @param[in] terminalWidth The width of the terminal window.
 */
void PrintAsterisk(int terminalWidth);

/**
 * @brief Prints left padding to center-align text in the terminal.
 *
 * This function prints spaces to the terminal to provide left padding,
 * which is useful for center-aligning text in the terminal.
 *
 * @param[in] terminalWidth The width of the terminal window.
 * @param[in] strLen        The length of the text to be centered.
 */
void PrintLeftPadding(int terminalWidth, int strLen);

/**
 * @brief Opens a file with the specified mode.
 *
 * This function opens a file with the specified file name and mode.
 *
 * @param[in] fileName The name of the file to be opened.
 * @param[in] mode     The mode in which the file should be opened ("r" for read, "w" for write, "a" for append, etc.).
 *
 * @return A pointer to the opened file if successful, or NULL if an error occurred.
 */
FILE *OpenFile(char *fileName, char *mode);

/**
 * @brief Reads mobile data from a file.
 *
 * This function reads mobile data from the specified file into the provided MobileData_t structure.
 *
 * @param[in]  file   A pointer to the file from which to read.
 * @param[out] mobile A pointer to the MobileData_t structure where the read data will be stored.
 *
 * @return Returns 1 upon successful read, FAILURE if an error occurred, or if end-of-file is reached.
 */
int ReadMobile(FILE *file, MobileData_t *mobile);

/**
 * @brief Asks for confirmation from the user.
 *
 * This function prompts the user to confirm an action by entering 'y' or 'n'.
 *
 * @return Returns SUCCESS if confirmed ('y' or 'Y') and FAILURE if cancelled ('n' or 'N'),
 *         or if an invalid input is provided.
 */
int Confirm();

/**
 * @brief Prints the header for displaying mobile data.
 *
 * This function prints the header with column labels for displaying mobile data.
 * The columns include MID (Mobile ID), Name, BrandName, Price, Discount (%), FinalPrice,
 * Flag, Quantity, Count, RAM (GB), Storage (GB), Chipset, and Camera (MP).
 */
void PrintHeader();

/**
 * @brief Prints the details of a mobile.
 *
 * This function prints the details of a mobile, including its ID, name, brand name,
 * price, discount, final price, display flag, quantity, count, RAM, storage, chipset,
 * and camera.
 *
 * @param[in] mobile The mobile data structure containing the details to be printed.
 */
void PrintMobileDetails(MobileData_t mobile);

/**
 * @brief Pauses execution until the Enter key is pressed.
 *
 * This function displays a message prompting the user to press Enter to continue,
 * and then waits for the user to press the Enter key.
 */
void Escape();

/**
 * @brief Pauses execution until the Enter key is pressed.
 *
 * This function displays a message prompting the user to press Enter to continue,
 * and then waits for the user to press the Enter key.
 */
void Escape1();

/**
 * @brief Gets an integer input from the user.
 *
 * This function prompts the user to enter an integer number, reads the input,
 * and stores it in the provided memory location.
 *
 * @param[out] num Pointer to the memory location where the entered integer will be stored.
 *
 */
void GetIntInput(int *num);

/**
 * @brief Gets a floating-point input from the user.
 *
 * This function prompts the user to enter a floating-point number, reads the input,
 * and stores it in the provided memory location.
 *
 * @param[out] num Pointer to the memory location where the entered float will be stored.
 *
 */
void GetFloatInput(float *num);

#endif