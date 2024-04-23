#include <stdio.h>

typedef struct
{
    double (*Area)(void *);
    double parameters[2];
    // void (*setter_ptr)(Shape_t *,char *, double, double);
} Shape_t;

double CalculateArea(Shape_t *obj)
{
    return obj->Area(obj);
}

double CalculateSquareArea(void *obj)
{
    Shape_t *square = (Shape_t *)obj;
    // printf("Enter length of square: ");
    // scanf("%lf", &square->parameters[0]);
    return square->parameters[0] *
           square->parameters[0];
}

double CalculateTriangleArea(void *obj)
{
    Shape_t *triangle = (Shape_t *)obj;
    return 0.5 * triangle->parameters[0] * triangle->parameters[1];
}

double CalculateRectangleArea(void *obj)
{
    Shape_t *rectangle = (Shape_t *)obj;
    return rectangle->parameters[0] * rectangle->parameters[1];
}

double CalculateCircleArea(void *obj)
{
    Shape_t *circle = (Shape_t *)obj;
    return 3.14 * circle->parameters[0] * circle->parameters[0];
}

void SquareSetter(Shape_t *obj, double length)
{
    obj->Area = CalculateSquareArea;
    obj->parameters[0] = length;
}

void TriangleSetter(Shape_t *obj, double base, double height)
{
    obj->Area = CalculateTriangleArea;
    obj->parameters[0] = base;
    obj->parameters[1] = height;
}

void RectangleSetter(Shape_t *obj, double length, double bradth)
{
    obj->Area = CalculateRectangleArea;
    obj->parameters[0] = length;
    obj->parameters[1] = bradth;
}

void CircleSetter(Shape_t *obj, double radius)
{
    obj->Area = CalculateCircleArea;
    obj->parameters[0] = radius;
}

int main()
{
    // Shape_t square = {CalculateSquareArea,{5,0.0}};
    // printf("%lf\n",square.Area(&square));
    int choice;
    Shape_t square;
    Shape_t triangle;
    Shape_t rectangle;
    Shape_t circle;
    double param1, param2;
    printf("For what you would like to find area?\n");
    printf("1. Square\n2. Triangle\n3. Rectangle\n4. Circle\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch (choice)

    {
    case 1:
        // square.Area = CalculateSquareArea;
        // double square_area = square.Area(&square);
        // printf("Area of Square is: %lf\n", square_area);
        printf("Enter length of square: ");
        scanf(" %lf", &param1);

        SquareSetter(&square, param1);
        printf("Area of Square is: %.2lf\n", CalculateArea(&square));
        break;

    case 2:
        // triangle.Area = CalculateTriangleArea;
        printf("Enter base of triangle: ");
        scanf(" %lf", &param1);
        printf("Enter height of triangle: ");
        scanf(" %lf", &param2);
        TriangleSetter(&triangle, param1, param2);
        printf("Area of Triangle is: %.2lf\n", CalculateArea(&triangle));
        break;
    case 3:
        // rectangle.Area = CalculateRectangleArea;
        // double rectangle_area = rectangle.Area(&rectangle);
        printf("Enter length of rectangle: ");
        scanf(" %lf", &param1);
        printf("Enter breadth of rectangle: ");
        scanf("%lf", &param2);
        RectangleSetter(&rectangle, param1, param2);
        printf("Area of Rectangle is: %lf\n", CalculateArea(&rectangle));
        break;
    case 4:
        // circle.Area = CalculateCircleArea;
        printf("Enter radius of circle: ");
        scanf(" %lf", &param1);
        CircleSetter(&circle, param1);
        printf("Area of Circle is: %lf\n", CalculateArea(&circle));
        break;

    default:
        printf("Enter Valid Choice!\n");
        break;
    }
    return 0;
}