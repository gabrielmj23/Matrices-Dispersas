# Archivo de objeto para las matrices
matriz.o: matriz.h matriz.c
	gcc -Wall -c matriz.c -o matriz.o

# Archivo de objeto para el programa principal
proy1.o: proy1.c matriz.h
	gcc -Wall -c proy1.c -o proy1.o

# Ejecutable
proy1: proy1.o matriz.o
	gcc -Wall proy1.o matriz.o -o proy1 