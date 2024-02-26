/**
 * @file app.c
 * @brief Main application file for Exercise-1
 */

#include <stdio.h>
#include "sampleLib.h"
#include "sampleAdd.h"

/**
 * \brief The main function.
 * 		\n Main entry point of the program.
 *
 * This function demonstrates the usage of the sampleAdd and sampleMultiply functions.
 * It takes two integer inputs from the user, performs addition and multiplication,
 * and prints the results.
 * @note This function assumes that sampleAdd and sampleMultiply are properly implemented.
 * @warning The user is responsible for providing valid integer inputs to avoid undefined behavior.
 */
void main()
{
	int a = 0, b = 0;
#ifdef DECORATE
	printf("###############################\r\n");
#endif
	printf("Enter first value:");
	scanf("%d", &a);
	printf("Enter second value:");
	scanf("%d", &b);
	printf("Addition of %d and %d is %d\r\n", a, b, sampleAdd(a, b));
	printf("Multiplication of %d and %d is %d\r\n", a, b, sampleMultiply(a, b));
#ifdef DECORATE
	printf("###############################\r\n");
#endif
}
