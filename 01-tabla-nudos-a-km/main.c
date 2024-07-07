#include <stdio.h>
#include "tabla.h"
#include "conversion.h"

double Incremento = 1;
int main(double inicio, double fin, double Incremento)
{
    double aux = inicio + Incremento;
    int i = 2;
    while (aux < fin)
    {
        aux += Incremento;
        i++;
    }
    double nudos[i];
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