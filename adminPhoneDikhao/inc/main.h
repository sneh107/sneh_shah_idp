/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file main.h
 * @brief Header file containing declarations related to main functionalities.
 *
 * This file contains function prototypes for the main functionalities of the
 * application, such as login, displaying the main menu, validating credentials,
 * viewing top sellers, and displaying all records.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Mar/18/2024, Sneh Shah, Created
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
 * @brief Logs in the user to the system.
 *
 * This function is responsible for authenticating the user by prompting for
 * username and password.
 *
 * @return Returns 0 if login is successful, -1 otherwise.
 */
int Login();

/**
 * @brief Displays the main menu.
 *
 * This function displays the main menu options available to the user.
 *
 */
void DisplayMainMenu();

/**
 * @brief Validates user credentials.
 *
 * This function validates the credentials entered by the user against the
 * stored credentials.
 *
 * @param[in]   username    The username entered by the user.
 * @param[in]   password    The password entered by the user.
 *
 * @return Returns 0 if credentials are valid, -1 otherwise.
 */
int ValidateCredentials(char *username, char *password);

/**
 * @brief Displays top sellers.
 *
 * This function displays the top selling items.
 *
 * @return Returns 0 upon success, -1 otherwise.
 */
int ViewTopSellers();

/**
 * @brief Displays all records.
 *
 * This function displays all records stored in the system.
 *
 * @return Returns 0 upon success, -1 otherwise.
 */
int DisplayAll();

#endif