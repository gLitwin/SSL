#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"
//#include "conversion.h"

int main(int argc, char* argv[])
{
    printf("no se");
    float Incremento = 1;
    float inicio = strtol(argv[1], NULL, 10);
    float fin = strtol(argv[2], NULL, 10);
    if(argc == 4){
        Incremento = strtol(argv[3], NULL, 10);
    }
    printf("%.3f - %.3f - %.3f\n",inicio, fin, Incremento);
    float aux = inicio + Incremento;
    int i = 1;
    printf("%.3f\n", aux);
    while (aux < fin)
    {
        aux += Incremento;
        i++;
        //printf("%d", i);
    }
    printf("%.3f\n", aux);
    float nudos[i];
    printf("%d\n",i);
    aux = inicio;
    int j = 0;
    printf("%.3f\n", aux);
    while (j < i)
    {
        printf("entro al while\n");
        nudos[j] = aux;
        printf("%.3f\n",nudos[j]);
        aux += Incremento;
        j++;
    }
    printf("salio del while\n");
    tabla(j,nudos);
    return 0;
}