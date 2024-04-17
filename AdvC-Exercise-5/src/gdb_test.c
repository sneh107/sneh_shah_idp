#include <stdio.h>
#include <stdlib.h>

void func3()
{
	int func3_var = 40;
	printf("Func3 Variable: %d\n", func3_var);
}

void func2()
{
	int func2_var = 30;
	printf("Func2 Variable: %d\n", func2_var);
	func3();
}

void func1()
{
	int func1_var = 20;
	printf("Func1 Variable: %d\n", func1_var);
	func2();
}

int main()
{
	int main_var = 10;
	// int *ptr=NULL;
	// *ptr = 20; //will give seg fault
	printf("Main Variable: %d\n", main_var);
	func1();
	return 0;
}
