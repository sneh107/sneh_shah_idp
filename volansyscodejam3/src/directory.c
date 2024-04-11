#include <stdio.h>
#include <string.h>
typedef enum
{
	SUCCESS = 0,
	/* define more status as you need */
	MAX_STATUS
}status_e;

struct Contact{
	char name[50];
	unsigned int num;
};

struct Contact contact[100];


/* void MySwap(struct Contact *x, struct Contact *y,int i, int j) */

/* void MySwap(struct Contact contact[100],int i, int j) */
/* { */
/*	struct Contact temp; */
/*	temp.name = contact[i].name; */
/*	contact[i].name =contact[j].name; */
/*	contact[j].name=temp.name; */

/*	temp.num=contact[i].num; */
/*	contact[i].num=contact[j].num; */
/*	contact[j].num=temp.num; */
/* } */



/**

*/
status_e sort_byname (const char *input_file, const char *output_file)
{
	status_e ret_val = SUCCESS;

	//***** Write your code here *****//
	//********************************//

	return ret_val;
}

status_e sort_bynumber (const char *input_file, const char *output_file)
{
	status_e ret_val = SUCCESS;
	/* struct Contact contact[100]; */

	//***** Write your code here *****//
	//********************************//
	FILE *fp=fopen(input_file,"r");
	if (fp==NULL){
		printf("Unable to open!\n");
	}
	/* while(fscanf(fp,"%s,%d",contact.name,&contact.num)==1) */
	for(int i=0;i<100;i++)
	{
		fscanf(fp,"%s,%u%*c",contact[i].name,&contact[i].num);
		/* printf("%s,%d\n",contact[i].name,contact[i].num); */
	}
	if(fp==NULL){
		fclose(fp);
	}
	for(int i=0;i<100;i++)
	{
		for(int j=i+1;j<100;j++)
		{
			if(contact[i].num>contact[j].num)
			{
				/* MySwap(&contact[i],&contact[j],i,j); */
				/* MySwap(contact,i,j); */
				struct Contact temp;
				char str[50];
				int numb;
				strcpy(str,contact[i].name);
				strcpy(contact[i].name,contact[j].name);
				strcpy(contact[j].name,str);
				/* str = contact[i].name; */
				/* contact[i].name =contact[j].name; */
				/* contact[j].name=str; */

				numb=contact[i].num;
				contact[i].num=contact[j].num;
				contact[j].num=numb;
			}
		}

	}
	fp=fopen(output_file,"w");
	if (fp==NULL){
		printf("Unable to open!\n");
	}
	for(int i=0;i<100;i++)
	{

		fprintf(fp,"%s,%u\n",contact[i].name,contact[i].num);
	}

	if (fp==NULL){
		fclose(fp);
	}
	return ret_val;
}

int main (int argc, char **argv)
{
	status_e status_byname, status_bynumber;
	const char *directory_unsorted = "directory_unsorted.csv";
	const char *directory_sorted_byname = "directory_sorted_byname.csv";
	const char *directory_sorted_bynumber = "directory_sorted_bynumber.csv";

	/* status_byname = sort_byname (directory_unsorted, directory_sorted_byname); */
	/* if (SUCCESS != status_byname) */
	/* { */
	/*	printf ("Sorting by name failed with [%d] error\n", status_byname); */
	/* } */

	status_bynumber = sort_bynumber (directory_unsorted, directory_sorted_bynumber);
	/* if (SUCCESS != status_bynumber) */
	/* { */
	/*	printf ("Sorting by number failed with [%d] error\n", status_bynumber); */
	/* } */

	return (status_byname | status_bynumber);
}
