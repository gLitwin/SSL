#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"
//#include "conversion.h"

int main(int argc, char* argv[])
{
    float Incremento = 1;
    float inicio = atof(argv[1]);
    float fin = atof(argv[2]);
    if(argc == 4){
        Incremento = atof(argv[3]);
    }
    printf("Las variables de inicio, fin e incremento son:\n");
    printf("%-g - %-g - %-g\n",inicio, fin, Incremento);
    float aux = inicio + Incremento;
    int i = 1;
    while (aux <= fin)
    {
        aux += Incremento;
        i++;
    }
    float nudos[i];
    aux = inicio;
    int j = 0;
    while (j < i)
    {
        nudos[j] = aux;
        aux += Incremento;
        j++;
    }
    tabla(j,nudos);
    return 0;
}