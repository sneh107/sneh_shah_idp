#include <stdio.h>
#include <string.h>

struct student
{
    char name[50];
    int age;
    float height;
}s1;

typedef struct student stu;
//or
typedef struct number
{
    int n;
}num;

void printStructure(struct student s)
{
    printf("%s,%d,%f\n",s.name,s.age,s.height);
}

int main()
{
    strcpy(s1.name,"sneh");
    s1.age=20;
    s1.height=6.0;

    struct student s2={"hello",19,5.9};
    struct student s3={.age=19,.name="hi",.height=8.9};
    stu s4={"bye",68,6.9};

    num n1;
    n1.n=10;
    // printf("%s,%d,%f\n",s1.name,s1.age,s1.height);
    // printf("%s,%d,%f\n",s2.name,s2.age,s2.height);
    // printf("%s,%d,%f\n",s3.name,s3.age,s3.height);
    // printf("%s,%d,%f\n",s4.name,s4.age,s4.height);
    printStructure(s1);
    printStructure(s2);
    printStructure(s3);
    printStructure(s4);
    printf("%d\n",n1.n);

    return 0;
}