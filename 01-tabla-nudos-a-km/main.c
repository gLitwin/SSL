#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"
#include "conversion.h"

int main(int argc, char* argv[])
{
    printf("no se");
    float Incremento = 1;
    float inicio = strtol(argv[1], NULL, 10);
    float fin = strtol(argv[2], NULL, 10);
    if(argc == 4){
        Incremento = strtol(argv[3], NULL, 10);
    }
    float aux = inicio + Incremento;
    int i = 2;
    while (aux < fin)
    {
        aux += Incremento;
        i++;
    }
    float nudos[i];
    aux = inicio;
    int j = 0;
    for (j; j < i; i++)
    {
        nudos[j] = aux;
        aux += Incremento;
    }
    nudos[j+1] = '\0';
    tabla(nudos);
    return 0;
}