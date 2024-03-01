#include <stdio.h>

struct book
{
    int bid;
    char name[50];
};

int main()
{
    FILE *file = fopen("myFile.txt", "a+");

    struct book books[3] = {
        {1, "Sneh"},
        {2, "Shah"},
        {3, "Sumit"}};

    for (int i = 0; i < 3; i++)
    {
        fprintf(file, "%d %s\n", books[i].bid, books[i].name);
    }
    rewind(file);

    struct book readBooks;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        sscanf(line, "%d %s", &readBooks.bid, readBooks.name);

        printf("%d %s\n", readBooks.bid, readBooks.name);
    }
    return 0;
}