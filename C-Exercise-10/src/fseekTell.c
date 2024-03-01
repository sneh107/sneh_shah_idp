#include <stdio.h>

struct book
{
    int bid;
    char name[50];
};

int main()
{
    struct book b;
    FILE *fp = fopen("myFile.txt", "r");
    int headerLength = 0;

    // while ((ch = fgetc(fp)) != '\n')
    //     headerLength++;
    while (fgetc(fp) != '\n')
        ;
    headerLength = ftell(fp);
    // printf("%d", headerLength);

    fseek(fp, headerLength, SEEK_SET);

    while (fscanf(fp, "%d %s", &b.bid, b.name) == 2)
    {
        printf("%d %s\n", b.bid, b.name);
    }

    return 0;
}