#include <stdio.h>

void printArray(int arr[]) //or void printArray(int *arr)
{
	printf("Array Elements: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ",arr[i]);
	}
    printf("\n");
}

int main()
{

	int arr[5] = { 10, 20, 30, 40, 50 };
	printArray(arr);
	return 0;
}