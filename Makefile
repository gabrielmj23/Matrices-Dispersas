# Archivo con funcionalidad básica de matrices
matriz.o: matriz.h matriz.c
	gcc -Wall -g -c matriz.o matriz.c

# Programa principal
proy1: proy1.c matriz.o
	gcc -Wall -g -o proy1 proy1.c matriz.o