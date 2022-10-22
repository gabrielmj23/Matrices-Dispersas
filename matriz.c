#include <stdlib.h>
#include "matriz.h"

// Crea una nueva matriz
Matriz *nueva_matriz(int nFilas, int nCols) {
	Matriz *m;

	// Reservar memoria y verificar errores
	if ( (m = (Matriz *)malloc(sizeof(Matriz))) == NULL ) {
		fprintf(stderr, "nueva_matriz: Error reservando memoria\n");
		exit(1);
	}

	// Agregar valores iniciales
	m->numFilas = nFilas;
	m->numColumnas = nCols;
	m->filas = NULL;
	return m;
}


// Crea una nueva fila
Fila *nueva_fila(int id) {
	Fila *f;

	// Reservar memoria y verificar errores
	if ( (f = (Fila *)malloc(sizeof(Fila))) == NULL ) {
		fprintf(stderr, "nueva_fila: Error reservando memoria\n");
		exit(1);
	}

	// Agregar valores iniciales
	f->id = id;
	f->col = NULL;
	f->next = NULL;
	return f;
}


// Crea una nueva columna
Columna *nueva_columna(int id, int val) {
	Columna *c;

	// Reservar memoria y verificar errores
	if ( (c = (Columna *)malloc(sizeof(Columna))) == NULL ) {
		fprintf(stderr, "nueva_columna: Error reservando memoria\n");
		exit(1);
	}

	// Agregar valores iniciales
	c->id = id;
	c->valor = val;
	c->next = NULL;
	return c;
}


// Copia la fila src en dest
Fila *copiar_fila(Fila *src, Fila *dest) {
	Columna *colSrc = src->col, *colDest = dest->col;
	while (colSrc) {
		colDest = nueva_columna(colSrc->id, colSrc->val);
		colDest = colDest->next;
		colSrc = colSrc->next;
	}
	return dest;
}


// Muestra en pantalla la matriz apuntada por matrizP
void imprimir_matriz(Matriz *matrizP) {
	if (!matrizP) {
		printf("La matriz se encuentra vacía\n");
		return;
	}

	register int i = 1, j = 1;
	Fila *filaAct = matrizP->filas;
	Columna *colAct;

	while (filaAct) {
		// Si no se han escrito filas entre la última y la actual, estarán llenas de 0
		for (; i < filaAct->id; i++) {
			for (j = 1; j <= matrizP->numColumnas; j++)
				printf("0 ");
			printf("\n");
		}

		// Imprimir fila actual
		j = 1;
		colAct = filaAct->col;
		while (col) {
			for (; j < colAct->id; j++)
				printf("0 ");
			printf("%i ", colAct->valor);
			col = col->next;
		}
		for (; j <= matrizP->numColumnas; j++)
			printf("0 ");
		printf("\n");
		++i;
		filaAct = filaAct->next;
	}

	// Escribir filas restantes que deberían estar después de la última que aparece en la lista
	for (; i <= matrizP->numFilas; i++) {
		for (j = 1; j <= matrizP->numColumnas; j++)
			printf("0 ");
		printf("\n");
	}
}