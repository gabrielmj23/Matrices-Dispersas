#include <stdlib.h>
#include <stdio.h>
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


// Pide entradas del usuario y devuelve una matriz llena
Matriz *rellenar_matriz() {
	// Pedir dimensiones
	int f, c;
	printf("Ingrese las dimensiones de la matriz (filas y columnas): ");
	scanf("%i %i", &f, &c);

	Matriz *nuevaM = nueva_matriz(f, c);
	// Crear fila y columna auxiliar
	nuevaM->filas = nueva_fila(1);
	Fila *filaAct = nuevaM->filas;
	Columna *colAct;
	register int i = 1, j;
	int val;

	// Pedir filas y columnas
	for (; i <= f; i++) {
		// Avanzar puntero de fila solo si ya se utilizó
		if (filaAct->col == NULL)
			filaAct->id = i;
		else {
			filaAct->next = nueva_fila(i);
			filaAct = filaAct->next;
		}

		printf("Fila %i: ", i);
		for (j = 1; j <= c; j++) {
			scanf("%i", &val);
			// Solo crear columna si el valor es distinto de 0
			if (val) {
				if (filaAct->col == NULL)
					colAct = filaAct->col = nueva_columna(j, val);
				else {
					colAct->next = nueva_columna(j, val);
					colAct = colAct->next;
				}
			}
		}
	}
	if (filaAct->col == NULL) {
		filaAct = NULL;
		free(filaAct);
	}
	return nuevaM;
}


// Libera la memoria reservada por matrizP y sus nodos hijos
void limpiar_matriz(Matriz *matrizP) {
	if (!matrizP) return;

	Fila *filaAct = matrizP->filas, *filaTmp;
	Columna *colAct, *colTmp;

	while (filaAct) {
		colAct = filaAct->col;
		while (colAct) {
			colTmp = colAct->next;
			free(colAct);
			colAct = colTmp;
		}
		filaTmp = filaAct->next;
		free(filaAct);
		filaAct = filaTmp;
	}
	free(matrizP);
}


// Copia la fila src en dest
Fila *copiar_fila(Fila *src, Fila *dest) {
	Columna *colSrc = src->col, *colDest = dest->col;
	while (colSrc) {
		colDest = nueva_columna(colSrc->id, colSrc->valor);
		colDest = colDest->next;
		colSrc = colSrc->next;
	}
	return dest;
}


// Muestra en pantalla la matriz apuntada por matrizP
void imprimir_matriz(Matriz *matrizP) {
	if (!matrizP || !matrizP->filas) {
		printf("La matriz se encuentra vacía\n");
		return;
	}

	register int i = 1, j;
	Fila *filaAct = matrizP->filas;
	Columna *colAct;

	while (filaAct != NULL) {
		// Si no se han escrito filas entre la última y la actual, estarán llenas de 0
		for (; i < filaAct->id; i++) {
			for (j = 1; j <= matrizP->numColumnas; j++)
				printf("0 ");
			printf("\n");
		}

		// Imprimir fila actual
		j = 1;
		colAct = filaAct->col;
		while (colAct) {
			for (; j < colAct->id; j++)
				printf("0 ");
			printf("%i ", colAct->valor);
			colAct = colAct->next;
			j++;
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
	printf("\n");
}


// Obtener un elemento de la matriz
int obt_elemento(int i, int j, Matriz *matrizP) {
  // Revisar si la matriz existe
  if (matrizP==NULL){
    fprintf(stderr, "obt_elemento: La matriz no existe\n");
    exit(1);
  }
  // Revisar si la ubicacion esta en la matriz
  if (i>matrizP->numFilas || j>matrizP->numColumnas){
    fprintf(stderr, "obt_elemento: El elemento esta fuera de las dimensiones de la matriz\n");
    exit(1);
  }
  // Buscar la fila
  Fila *fila_aux=matrizP->filas;
  for(; fila_aux!=NULL && fila_aux->id<i; fila_aux=fila_aux->next);

  //Si encuentra la fila, empieza a buscar la columna
  if (fila_aux && fila_aux->id==i) {
    Columna *columna_aux=fila_aux->col;
    for(; columna_aux!=NULL && columna_aux->id<j; columna_aux=columna_aux->next);
    if(columna_aux && columna_aux->id==j)
      //Si encuentra la columna, devuelve el valor
      return columna_aux->valor;
    //Si no encuentra el id de la columna, el valor será 0
    return 0;

  }
  //Si no encuentra el id de la fila el valor será 0
  return 0;
}


// Asignar valor a un elemento de la matriz
Matriz *asignar_elemento(int i, int j, int elemento, Matriz *matrizP) {
  // Revisar si la matriz existe
  if (matrizP==NULL){
    fprintf(stderr, "asignar_elemento: La matriz no existe\n");
    exit(1);
  }
  // Revisar si la ubicacion esta en la matriz
  if (i>matrizP->numFilas || j>matrizP->numColumnas){
    fprintf(stderr, "asignar_elemento: El elemento esta fuera de las dimensiones de la matriz\n");
    exit(1);
  }

  // Buscar la fila
  Fila *fila_aux=matrizP->filas;
  Fila *prev_fila=NULL;
  for (; fila_aux!=NULL && fila_aux->id<i; fila_aux=fila_aux->next)
    prev_fila=fila_aux;

  // Si encuentra la fila, empieza a buscar la columna
  if (fila_aux && fila_aux->id==i) {
    Columna *columna_aux=fila_aux->col;
    Columna *prev_col=NULL;
    for (; columna_aux!=NULL && columna_aux->id<j; columna_aux=columna_aux->next)
      prev_col=columna_aux;

    // Si encuentra la columna, asigna el elemento
    if (columna_aux && columna_aux->id==j) {
      columna_aux->valor=elemento;
      return matrizP;
    }
    // Si no encuentra el id de la columna la crea
    Columna *nColumna = nueva_columna(j,elemento);
    nColumna->next=columna_aux;
    if (prev_col!=NULL)
    	prev_col->next=nColumna;
    else
    	fila_aux->col = nColumna;
    return matrizP;

  }
  // Si no encuentra el id crea la fila y la columna
  Fila *nFila = nueva_fila(i);
  nFila->col=nueva_columna(j,elemento);
  nFila->next=fila_aux;

  if (prev_fila!=NULL)
  	prev_fila->next=nFila;
  else
  	matrizP->filas = nFila;
  
  return matrizP;
}
