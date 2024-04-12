/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file main.c
 * @brief Sorting contacts by name and number.
 *
 * This file contains function prototypes for  processing unsorted pocket directory
 * (directory_unsorted.csv) and creating 2 sorted directories. One directory
 * (directory_sorted_byname.csv) containing the entries sorted by name.
 * Another directory (directory_sorted_bynumber.csv) containing the entries
 * sorted by number.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Apr/11/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>

typedef enum
{
	SUCCESS = 0,
	/* define more status as you need */
	FAILURE = -1,
	MAX_STATUS
} status_e;

struct Contact
{
	char name[50];
	unsigned long long int num;
};

struct Contact contact[100];

/* void MySwap(struct Contact *x, struct Contact *y,int i, int j) */

/**
 * @brief Swaps two contacts.
 *
 * This function takes an array of contacts and the indices of two contacts,
 * then swaps their positions.
 * @param[in,out] contact Array of contacts.
 * @param[in] i Index of the one contact to be swapped.
 * @param[in] j Index of the second contact.
 */
void MySwap(struct Contact contact[100], int i, int j)
{
	struct Contact temp;
	temp = contact[i];
	contact[i] = contact[j];
	contact[j] = temp;
	// temp.name = contact[i].name;
	// contact[i].name = contact[j].name;
	// contact[j].name = temp.name;

	// temp.num = contact[i].num;
	// contact[i].num = contact[j].num;
	// contact[j].num = temp.num;
}

/**
 * @brief Sorts contacts by name.
 *
 * Reads contacts from input_file, sorts them by name, and writes to output_file.
 *
 * @param[in] input_file Path to the input file.
 * @param[in] output_file Path to the output file.
 * @return SUCCESS or FAILURE.
 */
status_e sort_byname(const char *input_file, const char *output_file)
{
	status_e ret_val = SUCCESS;

	//***** Write your code here *****//
	//********************************//
	FILE *fp = fopen(input_file, "r");
	if (fp == NULL)
	{
		printf("Unable to open!");
		ret_val = FAILURE;
		return ret_val;
	}

	for (int i = 0; i < 100; i++)
	{
		fscanf(fp, "%[^,],%llu\n", contact[i].name, &contact[i].num);
	}

	if (fp != NULL)
	{
		fclose(fp);
	}

	for (int i = 0; i < 100; i++)
	{
		for (int j = i + 1; j < 100; j++)
		{
			if (strcmp(contact[i].name, contact[j].name) > 0)
			{
				MySwap(contact, i, j);
			}
		}
	}

	fp = fopen(output_file, "w");
	if (fp == NULL)
	{
		printf("Unable to open!");
		ret_val = FAILURE;
		return ret_val;
	}
	for (int i = 0; i < 100; i++)
	{

		fprintf(fp, "%s,%llu\n", contact[i].name, contact[i].num);
	}

	if (fp != NULL)
	{
		fclose(fp);
	}

	return ret_val;
}

/**
 * @brief Sorts contacts by number.
 *
 * Reads contacts from input_file, sorts them by number, and writes to output_file.
 *
 * @param[in] input_file Path to the input file.
 * @param[in] output_file Path to the output file.
 * @return SUCCESS or FAILURE.
 */
status_e sort_bynumber(const char *input_file, const char *output_file)
{
	status_e ret_val = SUCCESS;
	/* struct Contact contact[100]; */

	//***** Write your code here *****//
	//********************************//
	FILE *fp = fopen(input_file, "r");
	if (fp == NULL)
	{
		printf("Unable to open!");
		ret_val = FAILURE;
		return ret_val;
	}
	/* while(fscanf(fp,"%s,%d",contact.name,&contact.num)==2) */
	for (int i = 0; i < 100; i++)
	{
		fscanf(fp, "%[^,],%llu\n", contact[i].name, &contact[i].num);
		/* printf("%s,%d\n",contact[i].name,contact[i].num); */
	}
	if (fp != NULL)
	{
		fclose(fp);
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = i + 1; j < 100; j++)
		{
			if (contact[i].num > contact[j].num)
			{
				/* MySwap(&contact[i],&contact[j],i,j); */
				/* MySwap(contact,i,j); */
				// struct Contact temp;
				// char str[50];
				// int numb;
				// strcpy(str, contact[i].name);
				// strcpy(contact[i].name, contact[j].name);
				// strcpy(contact[j].name, str);
				// /* str = contact[i].name; */
				// /* contact[i].name =contact[j].name; */
				// /* contact[j].name=str; */

				// numb = contact[i].num;
				// contact[i].num = contact[j].num;
				// contact[j].num = numb;
				// temp = contact[i];
				// contact[i] = contact[j];
				// contact[j] = temp;
				MySwap(contact, i, j);
			}
		}
	}
	fp = fopen(output_file, "w");
	if (fp == NULL)
	{
		printf("Unable to open!");
		ret_val = FAILURE;
		return ret_val;
	}
	for (int i = 0; i < 100; i++)
	{

		fprintf(fp, "%s,%llu\n", contact[i].name, contact[i].num);
	}

	if (fp == NULL)
	{
		fclose(fp);
	}
	return ret_val;
}

/**
 * @brief Main function.
 * @param[in] argc Number of command-line arguments.
 * @param[in] argv Array of command-line arguments.
 * @return SUCCESS or FAILURE.
 */
int main(int argc, char **argv)
{
	status_e status_byname, status_bynumber;
	const char *directory_unsorted = "./files/directory_unsorted.csv";
	const char *directory_sorted_byname = "./files/directory_sorted_byname.csv";
	const char *directory_sorted_bynumber = "./files/directory_sorted_bynumber.csv";

	status_byname = sort_byname(directory_unsorted, directory_sorted_byname);
	if (SUCCESS != status_byname)
	{
		printf("Sorting by name failed with [%d] error\n", status_byname);
	}

	status_bynumber = sort_bynumber(directory_unsorted, directory_sorted_bynumber);
	if (SUCCESS != status_bynumber)
	{
		printf("Sorting by number failed with [%d] error\n", status_bynumber);
	}

	return (status_byname | status_bynumber);
}