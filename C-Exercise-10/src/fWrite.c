#include <stdio.h>

struct book
{
    int bid;
    char name[50];
};

int main()
{
    struct book b[3] = {
        {1, "sneh"},
        {2, "shah"},
        {3, "sumit"}};

    FILE *fp = fopen("myFile.bin", "ab+");
    fwrite(b, sizeof(b), 1, fp); // writes all 3 because size of b
    // fwrite(b, sizeof(struct book), 2, fp);//writes first two
    // fwrite(&b[1], sizeof(struct book), 2, fp);//writes last two
    // fwrite(b, sizeof(struct book), 2, fp);
    // fwrite(b, sizeof(struct book), 2, fp);
    return 0;
}