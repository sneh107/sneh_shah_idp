/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file editMobile.h
 * @brief Header file containing declarations related to mobile editing functionalities.
 *
 * This file contains function prototypes for performing editing operations on mobile data.
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

#ifndef EDIT_H
#define EDIT_H

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
/* None */

/***********************
 * Global Variables
 ***********************/
extern int foundResult;  /**< Indicates whether mobiles are found during editing. */
extern char tempstr[50]; /**< Temporary string variable used in editing operations. */
int searchFlag;          /**< Flag indicating the search operation type. */

/************************
 * Function Prototypes
 ************************/

/**
 * @brief Performs editing operation on a mobile.
 *
 * This function allows the user to edit the details of a mobile.
 *
 * @param[in]   idToEdit    The ID of the mobile to be edited.
 *
 * @return Returns 0 upon success, -1 otherwise.
 */
int PerformEdit(int idToEdit);

/**
 * @brief Displays the edit menu for a mobile.
 *
 * This function displays the menu options for editing a mobile's details.
 *
 * @param[in]   mobile    Pointer to the mobile data structure to be edited.
 *
 * @return Returns 0 upon success, -1 otherwise.
 */
int DisplayEditMenu(MobileData_t *mobile);

/**
 * @brief Edits mobile data.
 *
 * This function performs the editing of mobile data based on user input.
 *
 * @return Returns 0 upon success, -1 otherwise.
 */
int EditMobile();

#endif