/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file includes.h
 * @brief Header file for common includes and structures.
 *
 * This file contains common include statements and a structure definition
 * used across the project.
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

#ifndef INCLUDE_H
#define INCLUDE_H

/*******************
 * Includes
 *******************/
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*************************
 * Defines
 *************************/
/* None */

/**************************************
 * Structures, Enumerations, Typedefs
 *************************************/
enum DisplayFlag
{
    new,
    refurbished,
    outdated,
    mostPurchased,
    outOfStock
};

typedef struct
{
    int id;
    char name[50];
    char brandName[50];
    float price;
    float discount;
    float finalPrice;
    enum DisplayFlag displayFlag;
    int quantity;
    int count;

    struct
    {
        int ram;
        int storage;
        char chipset[50];
        int camera;
    } config;
} MobileData_t;

/***********************
 * Global Variables
 ***********************/
/* None */

/************************
 * Function Prototypes
 ************************/
/* None */

#endif