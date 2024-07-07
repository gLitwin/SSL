#include <stdio.h>
#include "conversion.h"
#include "tabla.h"

void tabla(int filas, float nudos[]){
    printf("|\tNudos |\tKm/h |");
    for(int i = 0;i<filas; i++){
        printf("|\t%f |\t%f |", nudos[i], conversion(nudos[i]));
    }
    return;
}