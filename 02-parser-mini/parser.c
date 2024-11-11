#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "parser.h"

void parser() {
    initTablaTransicion();  // Inicializar la tabla de transición
    Programa(); //Comienza por el axioma a derivar
}

void Programa(){ //AXIOMA
    Token t = prox_token();
    match(PROGRAMA);
    printf("Programa: ");
    Identificador();
    printf("%s\n", t.lexema);
    ListaSentencias();
    printf("fin\n");
    match(FIN);
}

void ListaSentencias(){
    Sentencia();
    for(Token t = prox_token(); t.tipo != FIN; t = prox_token()){
        Sentencia();
    }
}

void Sentencia(){
    Token t = prox_token();
    if(t.tipo == IDENTIFICADOR){
        printf("sentencia asignacion\n");
        match(IDENTIFICADOR);
        match(ASIGNACION);
        Expresion();
    } else {
    switch (t.tipo)
    {
    case ENTERO:
        printf("sentencia declaracion\n");
        match(ENTERO);
        Identificador();
        break;
    case LEER:
        printf("sentencia leer\n");
        match(LEER);
        match(PARENTESIS_ABRE);
        ListaIdentificadores();
        match(PARENTESIS_CIERRA);
        break;
    case ESCRIBIR:
        printf("sentencia escribir\n");
        match(ESCRIBIR);
        match(PARENTESIS_ABRE);
        ListaExpresiones();
        match(PARENTESIS_CIERRA);
    break;
    default:
        ErrorSintactico();
    break;
    }
    }
    match(PUNTO_Y_COMA);
}

void ListaIdentificadores(){
    Identificador();
    Token t = prox_token();
    for(;t.tipo == COMA;t=prox_token()){
        match(COMA);
        Identificador();
    }
}

void ListaExpresiones(){
    Expresion();
    Token t = prox_token();
    for(;t.tipo == COMA;t=prox_token()){
        match(COMA);
        Expresion();
    }
}

void Expresion(){
    Termino();
    Token t = prox_token();
    for(;t.tipo == OPERADOR_MAS || t.tipo == OPERADOR_MENOS;t=prox_token()){
        match(t.tipo);
        Termino();
    }
}

void Termino(){
    Primaria();
    Token t = prox_token();
    for(;t.tipo == OPERADOR_MULTIPLICACION || t.tipo == OPERADOR_DIVISION || t.tipo == OPERADOR_MODULO;t=prox_token()){
        match(t.tipo);
        Primaria();
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
            match(PARENTESIS_ABRE);
            Expresion();
            match(PARENTESIS_CIERRA);
        break;
        case OPERADOR_MENOS:
            match(OPERADOR_MENOS);
            Expresion();
        break;
        default:
            ErrorSintactico();
        break;
    }
}
void Constante(){ //? Funciones evitables... pongo simplemente match(CONSTANTE)?
        match(CONSTANTE);
}

void Identificador(){ //? Funciones evitables... pongo simplemente match(IDENTIFICADOR)?
        match(IDENTIFICADOR);
}