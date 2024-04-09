// #include <stdio.h>
// 	void ArrayCheck(int *num,int arr[]){
// 	for(int i=0;i<3;i++)
// 	{
// 		if(arr[i]<arr[i+1])
// 		{
// 			*num--;
// 			ArrayCheck(num,arr);
// 		}
// 	}}
// int main(){
// 	int num,length=3,arr[50];
// 	printf("Hello World!\n");
// 	printf("Enter a number: ");
// 	scanf("%d",&num);

// 	for(int i=0;num!=0;i++)
// 	//while(num!=0)
// 	{
// 		int temp=num%10;
// 		arr[i]=temp;
// 		num=num/10;
// 	}

// 	for(int i=0;i<length;i++)
// 	{
// 		printf("arr %d: %d\n",i,arr[i]);

// 	}

// 	ArrayCheck(&num,arr);
// 	printf("Correct!\n");

// 	return 0;
// }

#include <stdio.h>
#include <string.h>
int main()
{
	char num[50];
	printf("Enter no. : ");
	scanf(" %s", num);
	int length = strlen(num);
	for (int i = length - 1; i >= 0; i--)
	{
		if (num[i] < num[i - 1])
		{
			num[i - 1]--;

			for (int j = i; j < length; j++)
			{
				num[j] = '9';
			}
		}
	}
	printf("%s\n", num);

	return 0;
}