#include <stdio.h>
#include "conversion.h"
#include "tabla.h"

void tabla(double nudos[]){
    int i = nudos[0];
    int j = 1;
    while(!(i='\0')){
        i = nudos[j];
        j++;
    }
    printf("|\tNudos |\tKm/h |");
    for(int i = 0;i<j; i++){
        printf("|\t%f |\t%f |", nudos[i], conversion(nudos[i]));
    }
    return;
}