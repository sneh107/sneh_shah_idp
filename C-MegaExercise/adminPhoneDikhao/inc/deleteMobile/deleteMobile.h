/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file deleteMobile.h
 * @brief Header file containing declarations related to mobile deletion functionalities.
 *
 * This file contains function prototypes for deleting mobile data and related operations.
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

#ifndef DELETE_H
#define DELETE_H

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
 * @brief Deletes a mobile record.
 *
 * This function deletes a mobile record from the database file. It first displays
 * outdated mobiles, prompts the user to enter the ID of the mobile to delete,
 * verifies the ID, and then deletes the corresponding record after confirmation.
 *
 * @return Returns SUCCESS if the mobile record is deleted successfully, otherwise FAILURE.
 */
int DeleteMobile();

/**
 * @brief Displays outdated mobile records.
 *
 * This function displays all outdated mobile records from the database file.
 * It opens the mobile data file, reads each record, and prints the details
 * of outdated mobiles.
 */
void DisplayOutdatedMobiles();

/**
 * @brief Checks if the provided ID is valid for deletion.
 *
 * This function prompts the user to enter the ID of the mobile to delete
 * and validates whether the ID corresponds to an outdated mobile in the database.
 * If the ID is found and corresponds to an outdated mobile, it returns SUCCESS;
 * otherwise, it returns FAILURE.
 *
 * @param[in,out] id Pointer to the integer variable where the user's input ID will be stored.
 * @return Returns SUCCESS if the ID is valid, FAILURE otherwise.
 */
int IsIdValid(int *id);

#endif