#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "parser.h"

#define MAX_LINE_LENGTH 256
#define MAX_KEY_LENGTH 128
#define MAX_VALUE_LENGTH 128

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} KeyValuePair;

void parser() {
    initTablaTransicion();  // Inicializar la tabla de transición
    Programa();
}

/* void parseFile(const char *filename) { //! esto lo hizo chatgpt
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    KeyValuePair kv;

    while (fgets(line, sizeof(line), file)) {
        // Eliminar el salto de línea al final de la línea
        line[strcspn(line, "\n")] = 0;

        // Separar clave y valor
        char *equals_sign = strchr(line, '=');
        if (equals_sign != NULL) {
            *equals_sign = '\0'; // Terminar la clave aquí
            strncpy(kv.key, line, MAX_KEY_LENGTH);
            strncpy(kv.value, equals_sign + 1, MAX_VALUE_LENGTH);
            printf("Key: '%s', Value: '%s'\n", kv.key, kv.value);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo_de_configuracion>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parseFile(argv[1]);
    return EXIT_SUCCESS;
} */

void Programa(){ //?      AXIOMA
    Token t = prox_token();
    if(t.tipo != PROGRAMA){
        ErrorSintactico();
    }
    match(t);
    printf("Programa: ");
    t = prox_token();
    Identificador();
    printf("%s\n", t.lexema);
    ListaSentencias();
    t = prox_token();
    if(t.tipo != FIN){
        ErrorSintactico();
    }
    printf("fin\n");
    match(t);
}

void ListaSentencias(){
    //TODO debe haber al menos una sentencia
    for(Token t = prox_token(); t.tipo != FIN; t = prox_token()){
        //printToken(t); //!borrar
        Sentencia();
    }
}

void Sentencia(){
    Token t = prox_token();
    if(t.tipo == IDENTIFICADOR){
        printf("sentencia asignacion\n");
        match(t);
        t = prox_token(t);
        if(t.tipo != ASIGNACION){
            ErrorSintactico();
        }
        match(t);
        Expresion();
    } else {
    switch (t.tipo) //TODO
    {
    case ENTERO:
        printf("sentencia declaracion\n");
        match(t);
        Identificador();
        break;
    case LEER:
        printf("sentencia leer\n");
        match(t);
        t = prox_token();
        if(t.tipo != PARENTESIS_ABRE){
            ErrorSintactico();
        }
        match(t);
        ListaIdentificadores();
        t = prox_token();
        if(t.tipo != PARENTESIS_CIERRA){
            ErrorSintactico();
        }
        match(t);
        break;
    case ESCRIBIR:
        printf("sentencia escribir\n");
        match(t);
        t = prox_token();
        if(t.tipo != PARENTESIS_ABRE){
            ErrorSintactico();
        }
        match(t);
        ListaExpresiones();
        t = prox_token();
        if(t.tipo != PARENTESIS_CIERRA){
            ErrorSintactico();
        }
        match(t);
    break;
    default:
        //printf("Error default, se esperaba inicio de sentencia, ");
        ErrorSintactico();
        break;
    }
    }
    t = prox_token(); //TODO estaría bien dejar de repetir el ';', está hecho así por los printf
    if(t.tipo != PUNTO_Y_COMA){
        ErrorSintactico();
    }
    match(t);
}

void ListaIdentificadores(){
    Identificador();
    Token t = prox_token();
    while(t.tipo == COMA){
        match(t);
        Identificador();
        t = prox_token();
    }
}

void ListaExpresiones(){
    Expresion();
    Token t = prox_token();
    while(t.tipo == COMA){
        match(t);
        Expresion();
        t = prox_token();
    }
}

void Expresion(){
    Termino();
    Token t = prox_token();
    while(t.tipo == OPERADOR_MAS || t.tipo == OPERADOR_MENOS){
        match(t);
        Termino();
        t = prox_token();
    }
}

void Termino(){
    Primaria();
    Token t = prox_token();
    while(t.tipo == OPERADOR_MULTIPLICACION || t.tipo == OPERADOR_DIVISION || t.tipo == OPERADOR_MODULO ){
        match(t);
        Primaria();
        t = prox_token();
    }
}

void Primaria(){
    Token t = prox_token();
    switch(t.tipo){
        case IDENTIFICADOR:
            Identificador();
        break;
        case CONSTANTE:
            Constante();
        break;
        case PARENTESIS_ABRE:
            match(t);
            Expresion();
            t = prox_token();
            if(t.tipo != PARENTESIS_CIERRA){
                ErrorSintactico();
            }
            match(t);
        break;
        case OPERADOR_MENOS:
            match(t);
            Expresion();
    }
}
void Constante(){
    Token t = prox_token();
        if(t.tipo != CONSTANTE)
        {ErrorSintactico();}
        match(t);
}


void Identificador(){
    Token t = prox_token();
        if(t.tipo != IDENTIFICADOR)
        {ErrorSintactico();}
        match(t);
}