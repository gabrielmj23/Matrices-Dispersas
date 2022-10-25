#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

#define MIN(a, b) (a < b) ? a : b
#define MIN_COL(c1, c2) (c1->id < c2->id) ? c1 : c2


/*
 * Prototipos de funciones solicitadas para el proyecto
 */
Matriz *sumar(const Matriz *m1, const Matriz *m2);


int main(void) {
	Matriz *m1 = rellenar_matriz();
	Matriz *m2 = rellenar_matriz();
	//Matriz *m3 = rellenar_matriz();

	Matriz *s12 = sumar(m1, m2);
	//Matriz *s13 = sumar(m1, m3);
	imprimir_matriz(s12);

	limpiar_matriz(m1);
	limpiar_matriz(m2);
	//limpiar_matriz(m3);
	limpiar_matriz(s12);
	//limpiar_matriz(s13);
	return 0;
}


/*
 * Implementación de funciones solicitadas para el proyecto
 */

// Sumar dos matrices -> Devuelve un puntero a la matriz conteniendo la suma
Matriz *sumar(const Matriz *m1, const Matriz *m2) {
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
	sum->filas = nueva_fila(1);
	register int idFilaAct = 1;
	Fila *f1 = m1->filas, *f2 = m2->filas, *fSum = sum->filas;
	Columna *c1, *c2, *minCol, *cSum = NULL;

	 	while (f1 != NULL && f2 != NULL) {
		// Crear fila
		idFilaAct = MIN(f1->id, f2->id);
		if (fSum->col != NULL) {
			fSum->next = nueva_fila(idFilaAct);
			fSum = fSum->next;
		}
		else
			fSum->id = idFilaAct;

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
			while (c1 != NULL && c2 != NULL) {
				// La lógica de las comparaciones es similar a la de las filas
				minCol = MIN_COL(c1, c2);
				if (c1->id != c2->id) {
					insertar_columna(&fSum, &cSum, minCol->id, minCol->valor);
					if(minCol == c1)
						c1 = c1->next;
					else
						c2 = c2->next;
				}
				else {
					// No se debe agregar la columna si los elementos suman 0
					int sumaCols = c1->valor + c2->valor;
					if (sumaCols)
						insertar_columna(&fSum, &cSum, c1->id, sumaCols);
					c1 = c1->next;
					c2 = c2->next;
				}
			}
			// Agregar columnas sobrantes
			while (c1) {
				insertar_columna(&fSum, &cSum, c1->id, c1->valor);
				c1 = c1->next;
			}
			while (c2) {
				insertar_columna(&fSum, &cSum, c2->id, c2->valor);
				c2 = c2->next;
			}
			f1 = f1->next;
			f2 = f2->next;
		}
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