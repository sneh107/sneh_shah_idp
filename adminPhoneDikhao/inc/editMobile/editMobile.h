#ifndef EDIT_H
#define EDIT_H

#include "../includes.h"

extern int foundResult;
extern char tempstr[50];
int searchFlag;

int PerformEdit(int idToEdit);
int DisplayEditMenu(MobileData_t *mobile);
int EditMobile();

#endif