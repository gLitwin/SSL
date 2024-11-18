# Nombre del ejecutable final
EXEC = compilador

# Archivos de entrada de Flex y Bison
LEX = scanner.l
YACC = parser.y

# Archivos generados por Flex y Bison
LEX_C = scanner.c
YACC_C = parser.c
YACC_H = parser.h

# Archivos de fuente adicionales
# SRC = main.c

# Compilador y opciones
CC = gcc
CFLAGS = -Wall -g

# Regla principal
all: $(EXEC)

# Generar scanner.c y parser.c automáticamente
$(LEX_C): $(LEX)
	flex -o $(LEX_C) $(LEX)

$(YACC_C) $(YACC_H): $(YACC)
	bison -d -o $(YACC_C) $(YACC)

# Compilar el ejecutable
$(EXEC): $(YACC_C) $(YACC_H) $(LEX_C) $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LEX_C) $(YACC_C) -lfl

# Limpieza de archivos generados
clean:
	rm -f $(LEX_C) $(YACC_C) $(YACC_H) $(EXEC) *.o

