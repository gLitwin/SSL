%option noinput
%option nounput
%option noyywrap
%option never-interactive
%option outfile="scanner.c" header-file="scanner.h"
%option yylineno

/* Codigo que va al header de scanner.c y scanner.h */
%{
#include "parser.h"
#include "helpers.h"
extern int erroresLexicos;
%}

/* Definiciones regulares */
LETRA           [a-zA-Z]
DIGITO          [0-9]
IDENTIFICADOR   {LETRA}({LETRA}|{DIGITO})*
CONSTANTE       {DIGITO}+
ESPACIO         [ \t\n\r]
COMENTARIO      "//".*

/* Reglas */
%%

"programa"        return PROGRAMA;
"fin"             return FIN;
"entero"          return ENTERO;
"leer"            return LEER;
"escribir"        return ESCRIBIR;

{IDENTIFICADOR} return IDENTIFICADOR;
{CONSTANTE}     return CONSTANTE;

":="            return ASIGNACION;

"+"             return OPERADOR_SUMA;
"-"             return OPERADOR_RESTA;
"*"             return OPERADOR_PRODUCTO;
"/"             return OPERADOR_DIVISION;
"%"             return OPERADOR_MODULO;

"("             return PARENTESIS_ABRE;
")"             return PARENTESIS_CIERRA;
","             return COMA;
";"             return PUNTO_Y_COMA;

{ESPACIO}       ; 
{COMENTARIO}    ; 

{DIGITO}+{IDENTIFICADOR}  {puts("34"); erroresLexicos++; return ERROR_CONSTANTE_INVALIDA;}  
{IDENTIFICADOR}[^a-zA-Z0-9\t\n\r \(\)\+\-\*\/\%\,\;:]+ {puts("34");erroresLexicos++; return ERROR_IDENTIFICADOR_INVALIDO;}
.               {puts("34");erroresLexicos++; return ERROR_CADENA_INVALIDA;}
%%