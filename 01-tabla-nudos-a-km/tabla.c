#include <stdio.h>
#include "conversion.h"
#include "tabla.h"

void tabla(int filas, float nudos[]){
    printf("| Nudos\t| Km/h\t\t|");
    for(int i = 0;i<filas; i++){
        printf("\n|    %-g\t|    %-g\t|", nudos[i], conversion(nudos[i]));
    }
    return;
}