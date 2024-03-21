// /*******************************************************************************
//  * Copyright(c) 2024, Volansys Technologies
//  *
//  * Description:
//  * @file searchMobile.h
//  * @brief Header file containing declarations related to mobile search functionalities.
//  *
//  * This file contains function prototypes for searching mobiles by name, brand, and
//  * displaying search results.
//  *
//  * Author       - Sneh Shah
//  *
//  *******************************************************************************
//  *
//  * History
//  *
//  * Mar/20/2024, Sneh Shah, Implemented mobile search functionality
//  *
//  * Mar/18/2024, Sneh Shah, Created
//  *
//  ******************************************************************************/

// #ifndef SEARCH_H
// #define SEARCH_H

// /*******************
//  * Includes
//  *******************/
// /* None */

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
// extern int foundResult;    /**< Indicates whether mobiles are found in the search. */
// extern char tempstr[50];   /**< Temporary string variable used in search operations. */

// /************************
//  * Function Prototypes
//  ************************/

// /**
//  * @brief Performs mobile search operation.
//  *
//  * This function allows the user to search for mobiles by various criteria.
//  *
//  */
// void SearchMobile();

// /**
//  * @brief Displays the search menu.
//  *
//  * This function displays the menu options for searching mobiles.
//  *
//  * @return Returns the user's choice from the menu.
//  */
// int DisplaySearchMenu();

// /**
//  * @brief Searches for mobiles by name.
//  *
//  * This function searches for mobiles by their names.
//  *
//  * @return Returns 0 upon success, -1 otherwise.
//  */
// int SearchByMobileName();

// /**
//  * @brief Searches for mobiles by brand name.
//  *
//  * This function searches for mobiles by their brand names.
//  *
//  * @return Returns 0 upon success, -1 otherwise.
//  */
// int SearchByBrandName();

// /**
//  * @brief Indicates whether mobiles are found in the search.
//  *
//  * This function is used to determine whether mobiles are found during the search operation.
//  *
//  * @param[in]   foundMobiles    The number of mobiles found in the search.
//  *
//  * @return Returns 1 if mobiles are found, 0 otherwise.
//  */
// int MobileFound(int foundMobiles);

// #endif

#ifndef SEARCH_H
#define SEARCH_H

int foundResult;
char tempstr[50];

void SearchMobile();
int DisplaySearchMenu();
int SearchByMobileName();
int SearchByBrandName();
int MobileFound(int foundMobiles);

#endif