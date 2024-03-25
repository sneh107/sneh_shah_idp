/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file buy_top_sellers.h
 * @brief Header file for buying top sellers.
 *
 * This file contains declarations for functions related to buying top sellers.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Mar/21/2024, Sneh Shah, Created
 *
 ******************************************************************************/
#ifndef BUY_H
#define BUY_H

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
 * @brief Buys the top-selling mobiles.
 *
 * This function allows the user to buy top-selling mobiles by entering the name
 * of the mobile to buy and the quantity. It also processes the purchase and updates
 * the mobile data and customer data files accordingly.
 *
 * @return 0 for success, -1 for failure.
 */
int BuyTopSellers();

/**
 * @brief Processes the purchase of a mobile.
 *
 * This function processes the purchase of a mobile by updating the mobile's data,
 * reducing the quantity available, and adding the purchase details to the customer data file.
 *
 * @param[in,out] mobile A pointer to the MobileData_t structure containing mobile data.
 * @param[in] file A pointer to the file containing mobile data.
 * @param[in] input_name The name of the mobile to buy.
 * @param[in] customer_name The name of the customer.
 * @param[in] buy_quantity The quantity of the mobile to buy.
 * @return Returns SUCCESS (0) for success, FAILURE (-1) for failure.
 */
int ProcessPurchase(MobileData_t *mobile, FILE *file, char input_name[], char customer_name[], int buy_quantity);

#endif