/**
 * @file 
 * @brief This file contains a simple program to calculate the area and perimeter of a circle.
*/


#include<stdio.h>
#define PI       3.1415   ///< Mathematical constant PI.
#define RADIUS_M 7.82     ///< Radius in meters
  
/**
 * @brief Calculates the Area of the circle.
 *
 * Formula: Area = PI*r^2
 * @param[in] radius
 * @param[out] area
 */ 
float calculate_area(float radius)
{
    float area;
    area = PI * radius * radius;
    return area;
}
  
/** 
 * @brief Calculates the Perimeter of the circle.
 *
 * Formula: Perimeter = 2*PI*r
 * @param radius The radius of the circle.
 * @return returns perimeter
*/
float calculate_perimeter(float radius)
{
    float perimeter;
    perimeter = 2 * PI * radius;
    return perimeter;
}
  
/** \brief The main function.
 *		\n Main entry point of the program.
 *
 * This function serves as the primary entry point for the program. It is executed when the program starts.
 * The main function initializes necessary resources, performs the main logic of the program, and may call
 * other functions to achieve specific tasks. Upon successful execution, it returns 0 to indicate completion
 * without errors.
*/
 
int main()
{
    float radius, area, perimeter;
    radius = RADIUS_M;
    area = calculate_area(radius);
    perimeter = calculate_perimeter(radius);
    printf("Area = %.2f sq.m \n", area);
    printf("perimeter = %.2f m\n", perimeter);
    return 0;
}
