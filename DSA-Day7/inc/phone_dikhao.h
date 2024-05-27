/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file phone_dikhao.h
 * @brief Header file containing declarations for managing a list of mobile phones.
 *
 * This header file provides declarations for functions and structures
 * to manage a list of mobile phones. It defines structures for representing
 * mobile phones and nodes in a doubly linked list, as well as function
 * prototypes for operations such as insertion, deletion, searching, and display.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * May/23/2024, Sneh Shah, Created
 *
 ******************************************************************************/
#ifndef MOBILE_H
#define MOBILE_H

/*******************
 * Includes
 *******************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

/**************************************
 * Structures, Enumerations, Typedefs
 *************************************/
/**
 * @brief Structure representing a mobile phone.
 */
typedef struct Mobilenode
{
    char name[50];
    char brandName[50];
    float price;
    int quantity;
} Mobile_t;

/**
 * @brief Structure representing a mobile node in a doubly linked list.
 */
typedef struct ListNode
{
    Mobile_t data;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode_t;

/**
 * @brief Enumeration representing exit status.
 */
typedef enum
{
    FAILURE = -1,
    SUCCESS
} exitStatus_e;

/************************
 * Function Prototypes
 ************************/

/**
 * @brief Inserts a mobile phone into the linked list.
 *
 * @param mobile The mobile phone to be inserted.
 * @return int Returns SUCCESS if insertion is successful, otherwise FAILURE.
 */
int InsertMobile(Mobile_t mobile);

/**
 * @brief Initializes the linked list.
 *
 * This function initializes the linked list with pre defined mobiles.
 */
void InitLinkedList();

/**
 * @brief Prints a line of asterisks to the terminal.
 *
 * This function prints a line of asterisks to the terminal with the specified width.
 *
 * @param[in] terminalWidth The width of the terminal window.
 */
void PrintAsterisk(int terminalWidth);

/**
 * @brief Prints left padding to center-align text in the terminal.
 *
 * This function prints spaces to the terminal to provide left padding,
 * which is useful for center-aligning text in the terminal.
 *
 * @param[in] terminalWidth The width of the terminal window.
 * @param[in] strLen        The length of the text to be centered.
 */
void PrintLeftPadding(int terminalWidth, int strLen);

/**
 * @brief Initializes the display for the Phone-Dikhao application.
 *
 * This function initializes the display by printing a welcome message and decorative asterisks.
 * It also determines the terminal width to adjust the display accordingly.
 */
void InitDisplay();

/**
 * @brief Pauses execution until the Enter key is pressed.
 *
 * This function displays a message prompting the user to press Enter to continue,
 * and then waits for the user to press the Enter key.
 */
void Escape();

/**
 * @brief Gets an integer input from the user.
 *
 * This function prompts the user to enter an integer number, reads the input,
 * and stores it in the provided memory location.
 *
 * @param[out] num Pointer to the memory location where the entered integer will be stored.
 *
 */
void GetIntInput(int *num);

/**
 * @brief Gets a floating-point input from the user.
 *
 * This function prompts the user to enter a floating-point number, reads the input,
 * and stores it in the provided memory location.
 *
 * @param[out] num Pointer to the memory location where the entered float will be stored.
 *
 */
void GetFloatInput(float *num);

/**
 * @brief Prints the details of a mobile.
 *
 * This function prints the details of a mobile, including its name, brand name,
 * price, quantity.
 *
 * @param[in] mobile The mobile data structure containing the details to be printed.
 */
void PrintMobileDetails(Mobile_t mobile);

/**
 * @brief Adds a new mobile phone to the list.
 *
 * This function prompts the user to enter details of a new mobile phone,
 * such as name, brand name, price, and quantity. It then validates the input
 * and adds the new mobile phone to the list using the InsertMobile() function.
 *
 * @return int Returns SUCCESS if the addition is successful, otherwise FAILURE.
 */
int AddMobile();

/**
 * @brief Inserts a mobile phone into the linked list.
 *
 * This function inserts a new node containing the given mobile phone
 * data into the doubly linked list. It inserts the new node
 * at the beginning of the list.
 *
 * @param mobile The mobile phone to be inserted.
 * @return int Returns SUCCESS if insertion is successful, otherwise FAILURE.
 */
int InsertMobile(Mobile_t mobile);

/**
 * @brief Displays the list of mobile phones.
 *
 * This function displays the details of all mobile phones in the store.
 * If the list is empty, it prints a message indicating that there are no
 * mobiles in the store.
 *
 * @return int Returns SUCCESS if the display is successful.
 */
int Displaylist();

/**
 * @brief Searches for a mobile phone by its name.
 *
 * This function prompts the user to enter the name of the mobile phone
 * they want to search for. It then iterates through the linked list
 * to find a match. If a match is found, it prints the details of the
 * matching mobile phone and returns 1. If no match is found, it prints
 * a message indicating no matching mobile found and returns 0.
 *
 * @return int Returns 1 if a matching mobile is found, otherwise returns 0.
 */
int SearchByMobileName();

/**
 * @brief Searches for mobile phones within a price range.
 *
 * Prompts the user to enter a minimum and maximum price range, then iterates through
 * the linked list to find mobile phones whose price falls within the specified range.
 * Prints the details of the found mobile phones and returns SUCCESS if any are found,
 * otherwise prints a message indicating no matching mobile found and returns FAILURE.
 *
 * @return 1 if successful, 0 otherwise.
 */
int SearchByPriceRange();

/**
 * @brief Allows the user to search for a mobile phone by name or price range.
 *
 * Displays options for searching by name, price range, going back, or exiting.
 * Handles user input and calls corresponding search functions.
 *
 * @return int Returns SUCCESS if the search is completed successfully.
 */
int SearchMobile();

/**
 * @brief Counts and displays the number of mobile phones in the store.
 *
 * Iterates through the linked list to count the number of mobile phones
 * and prints the count to the console.
 */
void NumberOfMobiles();

/**
 * @brief Deletes a mobile phone record from the store.
 *
 * Prompts the user to enter the name of the mobile phone to be deleted.
 * Searches for the mobile phone in the linked list and deletes it if found.
 * Handles cases where the mobile phone to be deleted is the only node,
 * the first node, the last node, or a node in between.
 *
 * @return int Returns SUCCESS if the deletion is successful, otherwise FAILURE.
 */
int DeleteMobile();

/**
 * @brief Edits the stock quantity of a mobile phone in the store.
 *
 * Prompts the user to enter the name of the mobile phone for which they want to update stocks.
 * Searches for the mobile phone in the linked list and prints its details if found.
 * Allows the user to enter the updated quantity for the mobile phone.
 * Validates the input and updates the quantity if valid.
 *
 * @return int Returns SUCCESS if the update is successful, otherwise FAILURE.
 */
int EditMobile();

/**
 * @brief Displays the main menu for managing mobile phones in the store.
 *
 * Displays options for adding, deleting, editing, searching, and viewing
 * mobile phone records, as well as viewing the total number of mobiles
 * and exiting the application. Handles user input and calls corresponding
 * functions to perform the selected operation. Allows three attempts for
 * entering a valid choice before exiting the application.
 */
void DisplayMainMenu();

/**
 * @brief Deletes the entire linked list of mobile phone records.
 *
 * Iterates through the linked list and frees the memory allocated for each node,
 * effectively deleting the entire list. Sets the head pointer to NULL.
 */
void DeleteList();

#endif