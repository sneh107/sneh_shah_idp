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
 * Mar/18/2024, Sneh Shah, Created
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
 * @return Returns SUCCESS (0) upon successful addition of the mobile device,
 *         FAILURE (-1) otherwise.
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
 * @return Returns SUCCESS (0) if the mobile device does not exist in the database,
 *         FAILURE (-1) otherwise.
 */
int CheckIfMobileExists(char *tempMobName);

/**
 * @brief Generates a unique ID for a new mobile device.
 *
 * This function reads the current ID from the file, increments it to generate
 * a new unique ID, and then updates the file with the new ID.
 *
 * @param[in,out] mobile Pointer to the structure containing mobile data.
 */
void GenerateUniqueId(MobileData_t *mobile);

/**
 * @brief Saves mobile data to the database.
 *
 * This function saves the provided mobile data to the database file.
 *
 * @param[in]   mobile     The mobile data to be saved.
 *
 * @return Returns SUCCESS (0) upon successful saving, FAILURE (-1) otherwise.
 */
int SaveToDB(MobileData_t *mobile);

#endif