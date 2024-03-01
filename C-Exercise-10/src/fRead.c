#include <stdio.h>

struct book
{
    int bid;
    char name[50];
};

int main()
{
    struct book b;

    FILE *fp = fopen("myFile1.bin", "rb");

    while (fread(&b, sizeof(struct book), 1, fp))
    {
        if (b.bid == 2)
        {
            printf("%d %s\n", b.bid, b.name);
        }
    }
    printf("\n");
    rewind(fp);
    while (fread(&b, sizeof(struct book), 1, fp))
    {
        printf("%d %s\n", b.bid, b.name);
    }

    return 0;
}