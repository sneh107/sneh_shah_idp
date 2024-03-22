#ifndef SEARCH_H
#define SEARCH_H

int FilterByPrice();
int FilterByConfig();
int DisplayConfigMenu();
int ViewByPriceRange(float *min_price, float *max_price);
int FilterByStorage();
int ViewByStorage(int *input_storage);
int FilterByRAM();
int ViewByRam(int *input_ram);
int MobileFound(int foundMobiles);
int FilterByChipset();
int ViewByChipset(char *input_chipset);
int FilterByCamera();
int ViewByCamera(int *input_camera);

#endif