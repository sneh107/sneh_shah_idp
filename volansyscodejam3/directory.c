/*
 ********************************************************************************
 Volansys Code Jam

 You need to write a code for the below mentioned problem statement.
 Read the rules before you proceed.

 ********************************************************************************

 Time Limit: 1 hour (15:00 to 16:00)
 Rule and Regulations:
 * Download this file and the supplementary material to your system.
 * Switch to Terminal mode by pressing CTRL+ALT+F3.
 * Use VI/VIM only.
 * No use of the internet. Not even on the phone. (we know who does)
 * No discussion. Do it on your own.
 * Doxygen commenting is mandatory on each function and file header.
 * Meaningful names should be used for the variable and the function.
 * The code should be properly indented.
 * The code should be compiled using makefile.
 * The code should compile with zero errors and warnings.
 * Submit the code within the defined time limit. Late submissions will not be
 accepted.
 * Create a separate branch with the name <volansyscodejam>. Upload the code in
 this branch.
 * The submission should have source files (*.c, *.h), makefile, doxygen, input
 files, output files only.

 ********************************************************************************
Introduction:
Those were the days when the old classic landline telephone ruled the world,
before wireless and subsequently smartphones took over.
It revolutionized communication across the globe and made it possible for the
masses to have access to it.
It did not have any electronic storage at that time and all the registered
numbers were printed in a book called a "Directory".
A directory has thousands and thousands of entries with registered names
(person, organization, or shop) and phone numbers sorted in alphabetical order
for ease of access.

An example of such a directory is,
Alexander,9876543210
Brian,9988776655
Cynthia,7896783451
Doctor,1234567890
Elly,4455667788

 ********************************************************************************
Requirement:
John Doe has a small diary which he is using as a pocket directory. He writes
down names and phone numbers in the diary but all the entries are unsorted.
You need to write a code to process John’s unsorted pocket directory
(directory_unsorted.csv) and create 2 sorted directories. One directory
(directory_sorted_byname.csv) should contain the entries sorted by name.
Another directory (directory_sorted_bynumber.csv) should contain the entries
sorted by number.
NOTE: CSV means Comma Separated Values

 ********************************************************************************
Example:
Input file (unsorted data):
Allen,9988551133
Clark,4598125430
Bruce,7722390143
Barry,5430985742
Victor,1234543210
Diana,3098756412

Output file (sorted data by name):
Allen,9988551133
Barry,5430985742
Bruce,7722390143
	Clark,4598125430
	Diana,3098756412
	Victor,1234543210

	Output (sorted data by number):
		Victor,1234543210
		Diana,3098756412
		Clark,4598125430
		Barry,5430985742
		Bruce,7722390143
		Allen,9988551133

		********************************************************************************
		*/

#include <stdio.h>

		typedef enum
{
	SUCCESS = 0,
	/* define more status as you need */
	MAX_STATUS
}status_e;

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

	//***** Write your code here *****//
	//********************************//

	return ret_val;
}

int main (int argc, char **argv)
{
	status_e status_byname, status_bynumber;
	const char *directory_unsorted = "directory_unsorted.csv";
	const char *directory_sorted_byname = "directory_sorted_byname.csv";
	const char *directory_sorted_bynumber = "directory_sorted_bynumber.csv";

	status_byname = sort_byname (directory_unsorted, directory_sorted_byname);
	if (SUCCESS != status_byname)
	{
		printf ("Sorting by name failed with [%d] error\n", status_byname);
	}

	status_bynumber = sort_bynumber (directory_unsorted, directory_sorted_bynumber);
	if (SUCCESS != status_bynumber)
	{
		printf ("Sorting by number failed with [%d] error\n", status_bynumber);
	}

	return (status_byname | status_bynumber);
}
