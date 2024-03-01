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

    struct book readBook;

    while (fscanf(file, "%d %s", &readBook.bid, readBook.name) == 2)
    {
        printf("%d %s\n", readBook.bid, readBook.name);
    }

    fclose(file);
    return 0;
}
