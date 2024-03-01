#include <stdio.h>
#include "header.h"

int i = 25;

int main() {
    printf("%d\n",i);
    i++;
    myFunction();
    mySecondFunction();
    
    return 0;
}
