#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

#define MIN(a, b) (a < b) ? a : b


/*
 * Prototipos de funciones solicitadas para el proyecto
 */
Matriz *sumar(Matriz *m1, Matriz *m2);


int main(void) {
	return 0;
}


/*
 * Implementación de funciones solicitadas para el proyecto
 */

// Sumar dos matrices -> Devuelve un puntero a la matriz conteniendo la suma
Matriz *sumar(Matriz *m1, Matriz *m2) {
	// Validar argumentos
	if (!m1 || !m2) {
		fprintf(stderr, "No se puede sumar si alguna matriz es nula\n");
		exit(1);
	}
	if (m1->numFilas != m2->numFilas || m1->numColumnas != m2->numColumnas) {
		fprintf(stderr, "No se puede sumar si las matrices tienen distintas dimensiones\n");
		exit(1);
	}

	// Inicializar matriz que almacena la suma y variables para el recorrido
	Matriz *sum = nueva_matriz(m1->numFilas, m1->numColumnas);
	register int filaAct = 1;
	Fila *f1 = m1->filas, *f2 = m2->filas, *fSum = sum->filas;
	Columna *c1, *c2, *cSum;

	while (f1 != NULL && f2 != NULL) {
		// Crear fila
		filaAct = MIN(f1->id, f2->id);
		if (fSum == NULL)
			fSum = nueva_fila(filaAct);
		else
			fSum->id = filaAct;

		// Si alguna es menor que la otra en id, copiarla y avanzar su puntero
		if (f1->id < f2->id) {
			fSum = copiar_fila(f1, fSum);
			f1 = f1->next;
		}
		else if (f2->id < f1->id) {
			fSum = copiar_fila(f2, fSum);
			f2 = f2->next;
		}
		// Si son iguales, recorrer columna a columna y sumar cuando sea posible
		else {
			c1 = f1->col;
			c2 = f2->col;
			cSum = fSum->col;
			while (c1 != NULL && c2 != NULL) {
				// La lógica de las comparaciones es similar a la de las filas
				if (c1->id < c2->id) {
					cSum = nueva_columna(c1->id, c1->valor);
					c1 = c1->next;
				}
				else if (c2->id < c1->id) {
					cSum = nueva_columna(c2->id, c2->valor);
					c2 = c2->next;
				}
				else {
					// No se debe agregar la columna si los elementos suman 0
					int sumaCols = c1->valor + c2->valor;
					if (sumaCols)
						cSum = nueva_columna(c1->id, sumaCols);
				}
				cSum = cSum->next;
			}
			f1 = f1->next;
			f2 = f2->next;
		}
		// Si todas las sumas resultaron 0, no se agregaron columnas y la fila no debería estar en la lista
		// Por lo tanto, solo se avanza el puntero si hay columnas agregadas
		if (fSum->col != NULL)
			fSum = fSum->next;
	}

	// Copiar filas que hayan sobrado (las listas pueden tener longitudes distintas)
	while (f1) {
		fSum = copiar_fila(f1, nueva_fila(f1->id));
		fSum = fSum->next;
		f1 = f1->next;
	}
	while (f2) {
		fSum = copiar_fila(f2, nueva_fila(f2->id));
		fSum = fSum->next;
		f2 = f2->next;
	}
	return sum;
}