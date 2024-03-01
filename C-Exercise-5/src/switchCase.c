#include <stdio.h>
#include <stdlib.h>

int main()
{
	char choice;
	int x, y;

	while (1) {
		printf("Enter the Operator (+,-,*,/)\nEnter x to exit\n");
		scanf(" %c", &choice);

		if (choice == 'x' || choice == 'X') {
			exit(0);
		}

		printf("Enter the two numbers: ");
		scanf("%d%d", &x, &y);

		switch (choice) {
		case '+':
			printf("%d + %d = %d\n", x, y, x + y);
			break;

		case '-':
			printf("%d - %d = %d\n", x, y, x - y);
			break;

		case '*':
			printf("%d * %d = %d\n", x, y, x * y);
			break;
		case '/':
			printf("%d / %d = %d\n", x, y, x / y);
			break;
		default:
			printf("Invalid Operator Input\n");
		}
	}
	return 0;
}