/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file search_mobile.h
 * @brief Header file for searching mobiles.
 *
 * This file contains declarations for functions related to searching mobiles by
 * price range, configuration, RAM, storage, chipset, and camera.
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

#ifndef SEARCH_H
#define SEARCH_H

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
 * @brief Filters mobiles by price range.
 *
 * This function filters mobiles based on the specified price range. It prompts
 * the user to enter the minimum and maximum prices, displays the mobiles within
 * that range, and allows the user to select a mobile for purchase.
 *
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int FilterByPrice();

/**
 * @brief Filters mobiles by configuration.
 *
 * This function displays the configuration menu and returns SUCCESS if the menu is displayed successfully.
 *
 * @return Returns SUCCESS (0) if the configuration menu is displayed successfully.
 */
int FilterByConfig();

/**
 * @brief Displays the configuration menu and allows the user to filter mobiles based on configuration.
 *
 * This function displays a menu where the user can choose to filter mobiles by various configurations
 * such as RAM, storage, chipset, and camera. It prompts the user to enter their choice and then calls
 * the corresponding filter function. It also handles the case where the user selects to go back or exit.
 *
 * @return Returns SUCCESS (0) if the menu is displayed successfully.
 */
int DisplayConfigMenu();

/**
 * @brief Displays mobiles within a specified price range.
 *
 * This function prompts the user to enter the minimum and maximum prices, and then
 * displays all the mobiles within that price range. It also checks for mobiles that
 * are not outdated or out of stock.
 *
 * @param[out] min_price The minimum price entered by the user.
 * @param[out] max_price The maximum price entered by the user.
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int ViewByPriceRange(float *min_price, float *max_price);

/**
 * @brief Filters mobiles by storage capacity.
 *
 * This function filters mobiles based on the specified storage capacity. It prompts
 * the user to enter the storage capacity, displays the mobiles with matching capacity,
 * and allows the user to select a mobile for purchase.
 *
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int FilterByStorage();

/**
 * @brief Displays mobiles with a specified storage capacity.
 *
 * This function prompts the user to enter the storage capacity and then displays
 * all the mobiles with the specified storage capacity. It ensures that the displayed
 * mobiles are not outdated or out of stock.
 *
 * @param[out] input_storage A pointer to the input storage capacity. This parameter
 * is used to store the user-entered storage capacity.
 *
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int ViewByStorage(int *input_storage);

/**
 * @brief Filters mobiles by RAM size.
 *
 * This function filters mobiles based on the specified RAM size. It prompts
 * the user to enter the RAM size, displays the mobiles with matching RAM size,
 * and allows the user to select a mobile for purchase.
 *
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int FilterByRAM();

/**
 * @brief Displays mobiles with a specified RAM size.
 *
 * This function prompts the user to enter the RAM size and then displays
 * all the mobiles with the specified RAM size. It also ensures that the
 * displayed mobiles are not outdated or out of stock.
 *
 * @param[out] input_ram A pointer to the input RAM size.
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int ViewByRam(int *input_ram);

/**
 * @brief Checks if mobiles are found.
 *
 * This function checks if any mobiles are found based on the search criteria.
 * If no mobiles are found, it prints a message indicating the absence of matching
 * mobiles; otherwise, it displays the count of found mobiles.
 *
 * @param[in] foundMobiles The number of mobiles found based on the search criteria.
 * @return Returns 1 if mobiles are found, FAILURE (-1) if no mobiles are found.
 */
int MobileFound(int foundMobiles);

/**
 * @brief Filters mobiles by chipset.
 *
 * This function filters mobiles based on the specified chipset. It prompts
 * the user to enter the chipset, displays the mobiles with matching chipset,
 * and allows the user to select a mobile for purchase.
 *
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int FilterByChipset();

/**
 * @brief Displays mobiles with a specified chipset.
 *
 * This function prompts the user to enter the chipset and then displays
 * all the mobiles with the specified chipset. It also ensures that the
 * displayed mobiles are not outdated or out of stock.
 *
 * @param[out] input_chipset A pointer to the input chipset.
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int ViewByChipset(char *input_chipset);

/**
 * @brief Filters mobiles by camera specifications.
 *
 * This function filters mobiles based on the specified camera specifications.
 * It prompts the user to enter the camera specifications, displays the mobiles
 * with matching specifications, and allows the user to select a mobile for purchase.
 *
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int FilterByCamera();

/**
 * @brief Displays mobiles with specified camera specifications.
 *
 * This function prompts the user to enter the camera specifications and then
 * displays all the mobiles with the specified camera specifications. It also
 * ensures that the displayed mobiles are not outdated or out of stock.
 *
 * @param[out] input_camera A pointer to the input camera specifications.
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int ViewByCamera(int *input_camera);

#endif