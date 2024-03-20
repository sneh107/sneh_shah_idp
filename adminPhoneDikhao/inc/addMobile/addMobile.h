/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file addMobile.h
 * @brief Header file containing declarations related to adding mobiles.
 *
 * This file contains function prototypes for adding mobile records to the
 * database. It includes functions for adding a mobile, checking if a mobile
 * already exists, generating a unique ID for a mobile, and saving mobile data
 * to the database.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Mar/20/2024, Sneh Shah, Updated SaveToDB function.
 *
 * Mar/18/2024, Sneh Shah, Created (description)
 *
 ******************************************************************************/
#ifndef ADD_H
#define ADD_H

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
/* None */

/************************
 * Function Prototypes
 ************************/

/**
 * @brief Adds a new mobile record.
 *
 * This function is responsible for adding a new mobile record to the database.
 *
 * @return Returns 0 upon success, -1 otherwise.
 */
int AddMobile();
// int askDetails();

/**
 * @brief Checks if a mobile already exists.
 *
 * This function checks if a mobile with the given name already exists in the
 * database.
 *
 * @param[in]   tempMobName     The name of the mobile to check.
 *
 * @return Returns 0 upon success, -1 otherwise.
 */
int CheckIfMobileExists(char *tempMobName);

/**
 * @brief Generates a unique ID for a mobile.
 *
 * This function generates a unique ID for a new mobile record.
 *
 * @param[in]   mobile     The mobile data structure for which the ID is generated.
 */
void GenerateUniqueId(MobileData_t *mobile);

/**
 * @brief Saves mobile data to the database.
 *
 * This function saves the provided mobile data to the database file.
 *
 * @param[in]   mobile     The mobile data to be saved.
 *
 * @return Returns 0 upon success, -1 otherwise.
 */
int SaveToDB(MobileData_t *mobile);

#endif