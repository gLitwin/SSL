#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

#define MAX_LINE_LENGTH 256
#define MAX_KEY_LENGTH 128
#define MAX_VALUE_LENGTH 128

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} KeyValuePair;

void parseFile(const char *filename) { //! esto lo hizo chatgpt
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
}

void Programa(){ //?      AXIOMA
    Token programa = {PALABRA_RESERVADA, "programa" }; 
    match(programa);
    Identificador();
    ListaSentencias();
    Token fin = {PALABRA_RESERVADA, "fin" }; 
    match(fin);
}

void ListaSentencias(){
    //TODO debe haber al menos una sentencia
    for(Token t = prox_token(); strcmp(t.lexema, "fin-prog"); t = prox_token()){
        Sentencia();
    }
}

void Sentencia(){
    Token t = prox_token();
    if(t.tipo == IDENTIFICADOR){
        match(t);
        Token tokenAsignacion = {ASIGNACION, ":="};
        match(tokenAsignacion);
        Expresion();
    } else {
    switch (t.lexema) //TODO
    {
    case "entero":
        match(t);
        Identificador();
        break;
    case "leer":
        match("leer");
        match("(");
        ListaIdentificadores();
        Token parentesisCierra = { PARENTESIS_CIERRA, ")" };
        match(parentesisCierra); //!!!!!!!!!!!!
        break;
    case "escribir":
        match("escribir");
        match("(");
        ListaExpresiones();
        Token parentesisCierra = { PARENTESIS_CIERRA, ")" };
        match(parentesisCierra); //!!!!!!!!!!!!!!
    default:
        ErrorSintactico(); //TODO 
        break;
    }
    }
    Token puntoComa = {PUNTO_Y_COMA, ";" };
    match(puntoComa); //!!!!!!!!!!!!!!
}

void listaIdentificadores(){
    Token t = prox_token();
    Identificador();
    while(t.tipo == COMA){
        match(t);
        Identificador();
    }
}

void listaExpresiones(){
    Token t = prox_token();
    Expresion();
    while(t.tipo == COMA){
        match(t);
        Expresion();
    }
}

void Expresion(){
    Token t = prox_token();
    Termino();
    while(t.tipo == OPERADOR_MAS || t.tipo == OPERADOR_MENOS){
        match(t);
        Termino();
    }
}

void Termino(){
    Primaria();
    Token t = prox_token();
    while(t.tipo == OPERADOR_MULTIPLICACION || t.tipo == OPERADOR_DIVISION || t.tipo == OPERADOR_MODULO ){
        match(t);
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
        match(t);
        Expresion();
        Token parentesisCierra = { PARENTESIS_CIERRA, ")" };
        match(parentesisCierra); //TODO COMO HACEMOS MATCH DE PARENTESISA QUE CIERRA
        break;
        case OPERADOR_MENOS:
        match(t);
        Expresion();
    }
}
void Constante(){
    Token t = prox_token()
    if(is_digit(t.lexema)){
        Digito();
        for(t = prox_token(); is_digit(t); t = prox_token)
        Digito();
    } else {
        ErrorSintactico();
    }
}


void Identificador(){
    Token t = prox_token();
    if(is_alpha(t)){
        match(t);
        while(1){
            t = prox_token();
            if(is_alpha(t) || is_digit(t)){
                match(t);
            } else {
                break;
            }
        }
    } else {
        ErrorSintactico();
    }
}
/* 
void Digito() {
    Token t = prox_token(); // Obtiene el siguiente token

    // Verifica si el token es un dígito
    if (t.lexema >= '0' && t.lexema <= '9') {
        match(t); // Coincide con el dígito
    } else {
        ErrorSintactico(); // Maneja el error si no es un dígito
    }
}

void PalabraReservada() {
    Token t = prox_token(); // Obtiene el siguiente token

    // Verifica si el token es un dígito
    if (es_palabra_reservada(t)) {
        match(t.lexema); // Coincide con el dígito
    } else {
        ErrorSintactico(); // Maneja el error si no es un dígito
    }
} */
/* 
void Letra() {
    Token t = prox_token(); // Obtiene el siguiente token

    // Verifica si el token es un dígito
    if (is_alpha(t.lexema)) {
        match(t.lexema); // Coincide con el dígito
    } else {
        ErrorSintactico(); // Maneja el error si no es un dígito
    }
} */
/* 
is_operador(char t){
    return t == '+' || t == '-' || t == '*' || t == '/' || t == '%';
} */
/* 
void Operador() {
    Token t = prox_token(); 

    if (is_operador(t.lexema)) {
        match(t.lexema); 
    } else {
        ErrorSintactico(); 
    }
} */

/* void Asignacion(){
    Token t = prox_token();
    if(t.tipo == ASIGNACION){
        match(t);
    } else {
        ErrorSintactico();
    }
} */

/* void CaracterPuntuacion(){
    Token t = prox_token();
    switch(t.tipo) {
        case PARENTESIS_ABRE:
            match(t);
        break;
        case PARENTESIS_CIERRA:
            match(t);
            break;
        case  PUNTO_Y_COMA:
            match(t);
            break;
        case COMA:
            match(t);
            break;    
        default:
            ErrorSintactico();
    }
    
} */


/* void Tokenfuncion(){ //AXIOMA, la llamamos TokenFunctino para que no colisione con el tipo Token
    Token t = prox_token();
    switch(t.tipo){
        case IDENTIFICADOR:
        Identificador();
        break;
        case CONSTANTE:
        Constante();
        break;
        case PALABRA_RESERVADA:
        PalabraReservada();
        break;
        case OPERADOR_DIVISION:
        case OPERADOR_MAS:
        case OPERADOR_MENOS:
        case OPERADOR_MODULO:
        case OPERADOR_MULTIPLICACION:
        Operador();
        break;
        case ASIGNACION:
        Asignacion();
        break;
        case PARENTESIS_ABRE:
        case PARENTESIS_CIERRA:
        case COMA:
        case PUNTO_Y_COMA:
        CaracterPuntuacion();
        break;
        default:
            ErrorSintactico();
    }
}
 */