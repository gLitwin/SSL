# Objetivo principal: generar el ejecutable
all: a.exe

# Generar parser.c y parser.h a partir de parser.y
parser.c parser.h: parser.y
	bison -d parser.y

# Generar scanner.c a partir de scanner.l, que depende de parser.h
scanner.c: scanner.l parser.h
	flex scanner.l

# Compilar el ejecutable final, enlazando con la librería flex
a.exe: parser.c scanner.c
	gcc -Wall parser.c scanner.c -o a.exe

# Limpiar archivos generados
clean:
	rm -f parser.c parser.h scanner.c a.exe
