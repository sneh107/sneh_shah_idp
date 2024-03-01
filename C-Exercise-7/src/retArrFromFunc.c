#include <stdio.h>

int* arrDoubler(int arr[])
{
    for (int i=0;i<5;i++)
    {
        arr[i]=2*arr[i];
    }
    return arr;
}

int main()
{
    int arr[]={10,20,30,40,50};
    int* ptr =arrDoubler(arr);

    printf("Doubled Array Elements: ");
    for(int i=0;i<5;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}
