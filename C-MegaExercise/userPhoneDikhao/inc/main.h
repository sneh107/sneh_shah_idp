/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file main.h
 * @brief Header file for main.c containing function declarations.
 *
 * This file contains declarations for functions defined in main.c, including
 * ViewTopSellers() and DisplayMainMenu().
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

#ifndef MAIN_H
#define MAIN_H

/*******************
 * Includes
 *******************/
/* None */

/*************************
 * Defines
 *************************/
/* None */

/**************************************
 * Structures, Enumerations, Typedefs
 *************************************/
/* None */

/***********************
 * Global Variables
 ***********************/
/* None */

/************************
 * Function Prototypes
 ************************/

/**
 * @brief Displays the list of top-selling mobiles.
 *
 * This function reads the mobile data from the file and prints the details
 * of the top-selling mobiles.
 *
 * @return Returns 0 upon success, -1 otherwise.
 */
int ViewTopSellers();

/**
 * @brief Displays the main menu and handles user input.
 *
 * This function presents the main menu options to the user and handles the
 * user's choice accordingly.
 */
void DisplayMainMenu();

#endif