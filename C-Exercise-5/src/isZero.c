#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num;
	printf("Enter no: ");
    while(scanf("%d",&num)!=1){
        while(getchar()!='\n');
        printf("Enter valid int\n");
    }
	
	
	if(num==0)
		printf("You Entered 0!\n");
	else if(num<0)
		printf("You Entered negative!\n");
	else
		printf("You Entered positive!\n");
    // else
	// 	printf("Enter Valid int!\n");

	return 0;
}