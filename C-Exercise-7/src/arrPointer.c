#include <stdio.h>

int main()
{

	int arr[5] = { 10, 20, 30, 40, 50 };
	int* ptr = arr;

	printf("Address Stored in pointer: %p\nAddress Stored in Array name: %p\nAddress of "
		"1st Array Element: %p\n", ptr,arr, &arr[0]);

	printf("Array elements using pointer: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ", *ptr); //or *(p + i)
        ptr++;
	}
    printf("\n");
	return 0;
}