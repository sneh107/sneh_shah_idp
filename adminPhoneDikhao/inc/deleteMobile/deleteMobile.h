// /*******************************************************************************
//  * Copyright(c) 2024, Volansys Technologies
//  *
//  * Description:
//  * @file deleteMobile.h
//  * @brief Header file containing declarations related to mobile deletion functionalities.
//  *
//  * This file contains function prototypes for deleting mobile data and related operations.
//  *
//  * Author       - Sneh Shah
//  *
//  *******************************************************************************
//  *
//  * History
//  *
//  * Mar/20/2024, Sneh Shah, Implemented mobile deletion functionality
//  *
//  * Mar/18/2024, Sneh Shah, Created
//  *
//  ******************************************************************************/

// #ifndef DELETE_H
// #define DELETE_H

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
// /* None */

// /************************
//  * Function Prototypes
//  ************************/

// /**
//  * @brief Deletes a mobile from the database.
//  *
//  * This function deletes a mobile from the database based on the provided ID.
//  *
//  * @return Returns 0 upon success, -1 otherwise.
//  */
// int DeleteMobile();

// /**
//  * @brief Displays outdated mobiles.
//  *
//  * This function displays the list of outdated mobiles available in the database.
//  *
//  */
// void DisplayOutdatedMobiles();

// /**
//  * @brief Validates the ID of a mobile.
//  *
//  * This function validates whether the provided ID corresponds to a valid mobile.
//  *
//  * @param[in]   id    Pointer to the ID of the mobile to be validated.
//  *
//  * @return Returns 0 if the ID is valid, -1 otherwise.
//  */
// int IsIdValid(int *id);

// #endif

#ifndef DELETE_H
#define DELETE_H

int DeleteMobile();
void DisplayOutdatedMobiles();
int IsIdValid(int *id);

#endif