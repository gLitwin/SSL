%{
#include <stdio.h>
#include "scanner.h"

int erroresLexicos;
int nroErrores;

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

%left OPERADOR_SUMA OPERADOR_RESTA
%left OPERADOR_PRODUCTO OPERADOR_DIVISION OPERADOR_MODULO
%right ASIGNACION
%nonassoc PARENTESIS_ABRE PARENTESIS_CIERRA
%precedence OPERADOR_RESTA_UNARIO


%%
program:
      PROGRAMA IDENTIFICADOR { 
          printf("programa: %s\n", $<str>2); 
          free($<str>2);  // Liberar memoria después de usar el identificador
      } listaSentencias FIN
    ;

listaSentencias:
      sentencia
    | listaSentencias sentencia
    ;

sentencia:
      ENTERO IDENTIFICADOR PUNTO_Y_COMA {printf("Sentencia declaración: %s \n", $<str>2);free($<str>2);}
    | IDENTIFICADOR ASIGNACION expresion PUNTO_Y_COMA {printf("Sentencia Asignacion\n");} 
    | LEER PARENTESIS_ABRE listaIdentificadores PARENTESIS_CIERRA PUNTO_Y_COMA {printf("Sentencia Leer\n");} 
    | ESCRIBIR PARENTESIS_ABRE listaExpresiones PARENTESIS_CIERRA PUNTO_Y_COMA {printf("Sentencia Escribir\n");}
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
    | expresion OPERADOR_SUMA termino { printf("suma\n"); }
    | expresion OPERADOR_RESTA termino { printf("resta\n"); }
    ;

termino:
      primaria
    | termino OPERADOR_PRODUCTO primaria { printf("multiplicación\n"); }
    | termino OPERADOR_DIVISION primaria { printf("división\n"); }
    | termino OPERADOR_MODULO primaria { printf("módulo\n"); }
    ;

primaria:
      IDENTIFICADOR
    | CONSTANTE
    | PARENTESIS_ABRE { printf("abre parentesis\n"); } expresion { printf("cierra parentesis\n"); } PARENTESIS_CIERRA
    | OPERADOR_RESTA primaria { printf("inversión\n"); }
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