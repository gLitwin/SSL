#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "scanner.h"

#define CANT_ESTADOS 18
#define CANT_COLUMNAS 16

int tablaTransicion[CANT_ESTADOS][CANT_COLUMNAS];

bool valueinarray(int val, int *arr, size_t n) {
    for(size_t i = 0; i < n; i++) {
        if(arr[i] == val)
            return true;
    }
    return false;
}

bool string_in_array(char* val, char**arr, size_t n) {
    for(size_t i = 0; i < n; i++) {
        if(!strcmp(val, arr[i]))
            return true;
    }
    return false;
}

bool is_error_token(Token token){
    int estado = token.tipo;
    int errores[] = {35,19,20,27,29};
    return (valueinarray(estado, errores , 5));
}

int is_alpha(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_digit(int c) {
    return c >= '0' && c <= '9';
}

void initTablaTransicion() {
    // Inicializar la tabla de transición manualmente
    int temp[CANT_ESTADOS][CANT_COLUMNAS] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 0, 16, 17},
        {1, 1, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19},
        {20, 2, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20},
        {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22},
        {23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23},
        {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},
        {25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25},
        {26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26},
        {27, 27, 27, 27, 27, 27, 27, 27, 9, 27, 27, 27, 27, 27, 27, 27},
        {28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29},
        {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
        {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31},
        {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32},
        {33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33},
        {34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34},
        {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 35, 35, 17}
    };

    // Copiar los valores a la variable global
    for (int i = 0; i < CANT_ESTADOS; i++) {
        for (int j = 0; j < CANT_COLUMNAS; j++) {
            tablaTransicion[i][j] = temp[i][j];
        }
    }
}

int getColumn(int c) {
    // El numero de columna comenzando desde el indice 0 para los caracteres alfanumericos

    if (is_alpha(c)) return 0;
    if (is_digit(c)) return 1;
    
    switch (c) {
        case '+': return 2;
        case '-': return 3;
        case '*': return 4;
        case '/': return 5;
        case '%': return 6;
        case ':': return 7;
        case '=': return 8;
        case '(': return 9;
        case ')': return 10;
        case ',': return 11;
        case ';': return 12;
        case ' ':
        case '\t':
        case '\n': return 13;
        case EOF: return 14;
        default: return 15;
    }
}

Token getNextToken() {
    Token token;
    int estado = 0;
    int i = 0;
    int caracter;

    token.lexema[0] = '\0'; // Inicializar lexema vacío para concatenar caracteres luego

    while (1) {
        caracter = getchar(); // Leer un caracter de stdin
        int columna = getColumn(caracter); // Obtener la columna a la que pertenece el caracter
        estado = tablaTransicion[estado][columna]; // Obtener el siguiente estado asociado 

        // Si el estado es -1 o mayor o igual a 18, se termina el bucle
        if (estado == -1 || estado >= 18) {
            ungetc(caracter, stdin);
            break;
        }

        // Si el estado es 0, se ignora el caracter
        if (estado != 0) {  // No agregar espacios al lexema
            token.lexema[i++] = caracter;
            token.lexema[i] = '\0';
        }
    }

    // Asignar el tipo de token según el estado final 
    switch (estado) {
        case 18: token.tipo = IDENTIFICADOR; break;
        case 21: token.tipo = CONSTANTE; break;
        case 22: token.tipo = OPERADOR_MAS; break;
        case 23: token.tipo = OPERADOR_MENOS; break;
        case 24: token.tipo = OPERADOR_MULTIPLICACION; break;
        case 25: token.tipo = OPERADOR_DIVISION; break;
        case 26: token.tipo = OPERADOR_MODULO; break;
        case 27: token.tipo = ERROR_ASIGNACION_DOS_PUNTOS; break;
        case 28: token.tipo = ASIGNACION; break;
        case 29: token.tipo = ERROR_ASIGNACION_IGUAL; break;
        case 30: token.tipo = PARENTESIS_ABRE; break;
        case 31: token.tipo = PARENTESIS_CIERRA; break;
        case 32: token.tipo = COMA; break;
        case 33: token.tipo = PUNTO_Y_COMA; break;
        case 34: token.tipo = FDT; break;
        case 35: token.tipo = ERROR_GENERAL; break;
        case 19: token.tipo = ERROR_IDENTIFICADOR; break;
        case 20: token.tipo = ERROR_CONSTANTE; break;
        default: token.tipo = ERROR_GENERAL; break;
    }

    return token;
}


void printToken(Token token) {
    switch (token.tipo) {
        case IDENTIFICADOR:
            printf("Identificador '%s'\n", token.lexema);
            break;
        case CONSTANTE:
            printf("Constante '%s'\n", token.lexema);
            break;
        case OPERADOR_MAS:
            printf("Más '%s'\n", token.lexema);
            break;
        case OPERADOR_MENOS:
            printf("Menos '%s'\n", token.lexema);
            break;
        case OPERADOR_MULTIPLICACION:
            printf("Multiplicación '%s'\n", token.lexema);
            break;
        case OPERADOR_DIVISION:
            printf("División '%s'\n", token.lexema);
            break;
        case OPERADOR_MODULO:
            printf("Módulo '%s'\n", token.lexema);
            break;
        case ASIGNACION:
            printf("Asignación '%s'\n", token.lexema);
            break;
        case PARENTESIS_ABRE:
            printf("Paréntesis que abre '%s'\n", token.lexema);
            break;
        case PARENTESIS_CIERRA:
            printf("Paréntesis que cierra '%s'\n", token.lexema);
            break;
        case COMA:
            printf("Coma '%s'\n", token.lexema);
            break;
        case PUNTO_Y_COMA:
            printf("Punto y coma '%s'\n", token.lexema);
            break;
        case FDT:
            printf("Fin de archivo\n");
            break;
        case ERROR_GENERAL:
            printf("Error general '%s'\n", token.lexema);
            break;
        case ERROR_IDENTIFICADOR:
            printf("Error de identificador '%s'\n", token.lexema);
            break;
        case ERROR_CONSTANTE:
            printf("Error de constante '%s'\n", token.lexema);
            break;
        case ERROR_ASIGNACION_DOS_PUNTOS:
            printf("Error en asignación por : solo '%s'\n", token.lexema);
            break;
        case ERROR_ASIGNACION_IGUAL:
            printf("Error en asignación por = solo '%s'\n", token.lexema);
            break;
        case PROGRAMA:
            printf("Palabra reservada: programa\n");
            break;
        case FIN:
            printf("Palabra reservada: fin\n");
            break;
        case ENTERO:
            printf("Palabra reservada: entero\n");
            break;
        case ESCRIBIR:
            printf("Palabra reservada: escribir\n");
            break;
        case LEER:
            printf("Palabra reservada: leer\n");
            break;
    }
}


char *palabras_reservadas[] = {
    "programa", "entero", "fin", "escribir", "leer"
};

static bool debo_escanear = true;
static Token token_actual;

Token reemplazarIdentificadorPorReservada(Token token){
    if(!strcmp(token.lexema, "programa"))
        token.tipo = PROGRAMA;
    if(!strcmp(token.lexema, "fin"))
        token.tipo = FIN;
    if(!strcmp(token.lexema, "entero"))
        token.tipo = ENTERO;
    if(!strcmp(token.lexema, "leer"))
        token.tipo = LEER;
    if(!strcmp(token.lexema, "escribir"))
        token.tipo = ESCRIBIR;
    return token;
}

Token prox_token(void)
{
	if (debo_escanear) {
		token_actual = getNextToken();
		while (is_error_token(token_actual)) {
            printToken(token_actual);          
			token_actual = getNextToken();
		}
		debo_escanear = false;
		if (token_actual.tipo == IDENTIFICADOR) {            
			int es_palabra_reservada = string_in_array(token_actual.lexema, palabras_reservadas, 5);
			if(es_palabra_reservada) {
				token_actual = reemplazarIdentificadorPorReservada(token_actual); 
            }
		}
	}
	return token_actual;
}

bool son_tokens_iguales(Token token1, Token token2){
    bool resultado = (token1.tipo == token2.tipo) && !strcmp(token1.lexema, token2.lexema);
    return resultado;
}

void ErrorSintactico(){
    Token t = prox_token();
    printf("Error sintactico, no se esperaba el token: ");
    printToken(t);
    //exit(1);
}

void match(TokenType t)
{
	if (t != prox_token().tipo)
		ErrorSintactico(prox_token());
	debo_escanear = true;
    prox_token(); //esta invocación es para que no haya necesidad de llamar prox_token() entre llamados de match()
}