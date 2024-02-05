#include <stdio.h>
//#include "sampleLib.h"
#include "./commonMod1/sampleAdd.h"
#include "./commonMod1/sampleSub.h"
#include "./commonMod2/sampleMultiply.h"
#include "./commonMod2/sampleDivide.h"

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
	printf("Addition of %d and %d is %d\r\n", a, b, sampleAdd(a,b));
	printf("Addition of %d and %d is %d\r\n", a, b, sampleSub(a,b));
	printf("Multiplication of %d and %d is %d\r\n", a, b, sampleMultiply(a,b));
	printf("Division of %d by %d is %d\r\n", a, b, sampleDivide(a, b));
#ifdef DECORATE
	printf("###############################\r\n");
#endif
}
