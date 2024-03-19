#ifndef STRUCT_H
#define STRUCT_H

enum DisplayFlag
{
    new,
    refurbished,
    outdated,
    mostPurchased,
    outOfStock
};

typedef struct
{
    int id;
    char name[50];
    char brandName[50];
    float price;
    float discount;
    float finalPrice;
    enum DisplayFlag displayFlag;
    int quantity;
    int count;

    struct
    {
        int ram;
        int storage;
        char chipset[50];
        int camera;
    } config;
} MobileData;

#endif