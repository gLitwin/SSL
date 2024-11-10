#include <stdio.h>
#include "scanner.h"

int main() {
    Token token;

    initTablaTransicion();  // Inicializar la tabla de transición

    parser();
    
    return 0;
}