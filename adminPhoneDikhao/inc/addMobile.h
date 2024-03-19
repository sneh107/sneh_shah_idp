#ifndef ADD_H
#define ADD_H

int askDetails();
int checkIfMobileExists(char *tempMobName);
void generateUniqueId(MobileData *mobile);
int saveToDB(MobileData *mobile);

#endif