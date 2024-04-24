#include <stdio.h>

int main()
{
	int doll_count=0;
	// printf("Hello World\n");

	int arr[doll_count];
	int test_case_count=0;

	printf("Enter test cases: ");
	scanf("%d",&test_case_count);

	for (int k=0;k<test_case_count;k++)
	{

		printf("Enter no. of dolls: \n");
		scanf(" %d",&doll_count);

		/* int visited_node[100]; */
		/* int visited_count=0; */
		for(int i=0;i<doll_count;i++)
		{
			scanf("%d",&arr[i]);
		}



		int temp_count=0;
		for(int i=0;i<doll_count;i++)
		{
			// int temp=arr[i];
			for(int j=0;i<doll_count;j++)
			{
				if(arr[i]==arr[j])
				{
					temp_count++;
				}
			}
			if(temp_count%2!=0)
			{
				printf("%d is not paired",arr[i]);
				// return 0;
			}
		}

	}
	return 0;
}
