# Generar parser.c y parser.h a partir de parser.y
parser.c parser.h: parser.y
	bison -d parser.y

# Generar scanner.c a partir de scanner.l
scanner.c: scanner.l
	flex scanner.l

# Compilar el ejecutable final, incluyendo las dependencias en parser.h
a.exe: parser.c scanner.c
	gcc parser.c scanner.c -o a.exe
#CC = gcc
#CFLAGS = -Wall -Wextra
#FLEX = flex
#
## Archivos objeto necesarios
#OBJS = scanner.o main.o parser.o
#
## Nombre del ejecutable
#TARGET = parser
#
#all: $(TARGET)
#
## Regla principal para crear el ejecutable
#$(TARGET): $(OBJS)
#	$(CC) $(OBJS) -o $(TARGET)
#
## Generación de parser.c y parser.h usando Bison
#parser.c parser.h: parser.y
#	bison -d parser.y
#
## Generar scanner.c y scanner.h desde scanner.l
#scanner.c scanner.h: scanner.l
#	flex scanner.l
#
## Compilación del archivo parser.tab.c generado por Bison
#parser.o: parser.c parser.h
#	gcc -c parser.c -o parser.o
#
## Compilar scanner.c
#scanner.o: scanner.c scanner.h tokens.h
#	$(CC) $(CFLAGS) -c scanner.c
#
## Compilar main.c
#main.o: main.c tokens.h scanner.h
#	$(CC) $(CFLAGS) -c main.c
#
#clean:
#	rm -f $(TARGET) $(OBJS) scanner.c scanner.h
#
#.PHONY: all clean