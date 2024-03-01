#include <stdio.h>
#include <string.h>

struct Student
{
    int roll_no;
    char name[30];
    char branch[40];
    int batch;
};

struct Student s, *ptr;

int main()
{
    ptr = &s;

    printf("Enter the Roll Number of Student: ");
    scanf("%d", &ptr->roll_no);
    // getchar();
    printf("Enter Name of Student: ");
    // fgets(ptr->name, 30, stdin);
    scanf(" %[^\n]s", ptr->name);
    // getchar();
    printf("Enter Branch of Student: ");
    // fgets(ptr->branch, 40, stdin);
    scanf(" %[^\n]s", ptr->branch);
    printf("Enter batch of Student: ");
    scanf("%d", &ptr->batch);

    printf("\nStudent details are: \n");
    printf("Roll No: %d\n", ptr->roll_no);
    printf("Name: %s\n", ptr->name);
    printf("Branch: %s\n", ptr->branch);
    printf("Batch: %d\n", ptr->batch);

    return 0;
}