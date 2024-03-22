#ifndef BUY_H
#define BUY_H

#include "../includes.h"

int BuyTopSellers();
int ProcessPurchase(MobileData_t *mobile, FILE *file, char input_name[], char customer_name[], int buy_quantity);

#endif