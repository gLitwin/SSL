%{
#include <stdio.h>
#include "scanner.h"
#include "helpers.h"

extern int erroresLexicos;
extern int errores;

extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern void yyerror(char*);
int variable=0;
char *token_names[] = {
    "FDT", "PROGRAMA", "FIN", "ENTERO", "LEER", "ESCRIBIR",
    "IDENTIFICADOR", "CONSTANTE", "ASIGNACION", "OPERADOR_SUMA",
    "OPERADOR_RESTA", "OPERADOR_PRODUCTO", "OPERADOR_DIVISION", 
    "OPERADOR_MODULO", "PARENTESIS_ABRE", "PARENTESIS_CIERRA", 
    "COMA", "PUNTO_Y_COMA", "ERROR_IDENTIFICADOR_INVALIDO",
    "ERROR_CONSTANTE_INVALIDA", "ERROR_CADENA_INVALIDA"
    };
%}
%defines "parser.h"
%output "parser.c"
%start program

%union {
	int    num;
	double real;
	char   *str;
}

%token PROGRAMA FIN ENTERO LEER ESCRIBIR
%token <num> CONSTANTE
%token IDENTIFICADOR
%token ASIGNACION OPERADOR_SUMA OPERADOR_RESTA OPERADOR_PRODUCTO
%token OPERADOR_DIVISION OPERADOR_MODULO PARENTESIS_ABRE PARENTESIS_CIERRA
%token COMA PUNTO_Y_COMA
%token ERROR_CADENA_INVALIDA ERROR_IDENTIFICADOR_INVALIDO ERROR_CONSTANTE_INVALIDA

%type <str> IDENTIFICADOR

%%
program:
      {printf("programa:");} PROGRAMA IDENTIFICADOR {printf("%s \n", $<str>2);} listaSentencias FIN
    ;


listaSentencias:
      sentencia
    | listaSentencias sentencia
    ;

sentencia:
      {printf("Sentencia Declaracion\n");} ENTERO IDENTIFICADOR {printf("%s \n", $<str>2);} PUNTO_Y_COMA
    | {printf("Sentencia Asignacion\n");} IDENTIFICADOR ASIGNACION expresion PUNTO_Y_COMA
    | {printf("Sentencia Leer\n");} LEER PARENTESIS_ABRE listaIdentificadores PARENTESIS_CIERRA PUNTO_Y_COMA
    | {printf("Sentencia Escribir\n");} ESCRIBIR PARENTESIS_ABRE listaExpresiones PARENTESIS_CIERRA PUNTO_Y_COMA
    ;

listaIdentificadores:
      IDENTIFICADOR
    | listaIdentificadores COMA IDENTIFICADOR
    ;

listaExpresiones:
      expresion
    | listaExpresiones COMA expresion
    ;

expresion:
      termino
    | expresion OPERADOR_SUMA {printf("suma\n");} termino
    | expresion OPERADOR_RESTA {printf("resta\n");} termino
    ;

termino:
      primaria
    | termino OPERADOR_PRODUCTO {printf("producto\n");}primaria
    | termino OPERADOR_DIVISION {printf("dicision\n");} primaria
    | termino OPERADOR_MODULO {printf("modulo\n");} primaria
    ;

primaria:
      IDENTIFICADOR
    | CONSTANTE
    | PARENTESIS_ABRE {printf("abre parentesis\n");} expresion PARENTESIS_CIERRA {printf("cierra parentesis\n");}
    | OPERADOR_RESTA expresion
    ;

%%

int main() {
  int status = 3;
	switch( yyparse() ){
	case 0:
		puts("Compilacion terminada con exito\n");
    status = 0;
  break;
	case 1:
		puts("Ocurrio un error\n"); status = 1;
  break;
	case 2:
		puts("Memoria insuficiente\n"); status = 2;
  break;
	}
  printf("Errors sintácticos: %d - Errores léxicos: %d\n", nroErrores - erroresLexicos, erroresLexicos);
	return status;
}
/* Informa la ocurrencia de un error. */
void yyerror(char *s){
    printf("%s\n",s);
    nroErrores++;
	return;
}
