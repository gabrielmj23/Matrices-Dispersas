#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

#define MIN(a, b) (a < b) ? a : b
#define MIN_COL(c1, c2) (c1->id < c2->id) ? c1 : c2


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
	f->primeraCol = NULL;
	f->ultCol = NULL;
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


// Agrega una nueva columna a filaP siguiente a su última columna
Fila *insertar_col_final(Fila *filaP, Columna *nuevaC) {
	// Agrega al inicio de la fila
	if (!filaP->primeraCol)
		filaP->primeraCol = filaP->ultCol = nuevaC;

	// Agrega al final
	else
		filaP->ultCol = filaP->ultCol->next = nuevaC;
	return filaP;
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
	register int i = 1, j;
	int val;

	// Pedir filas y columnas
	for (; i <= f; i++) {
		// Avanzar puntero de fila solo si ya se utilizó
		if (filaAct->primeraCol == NULL)
			filaAct->id = i;
		else {
			filaAct->next = nueva_fila(i);
			filaAct = filaAct->next;
		}

		printf("Fila %i: ", i);
		for (j = 1; j <= c; j++) {
			scanf("%i", &val);
			// Solo crear columna si el valor es distinto de 0
			if (val) 
				filaAct = insertar_col_final(filaAct, nueva_columna(j,val));
		}
	}
	if (filaAct->primeraCol == NULL) {
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
		colAct = filaAct->primeraCol;
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
	Columna *colSrc = src->primeraCol;
	while (colSrc) {
		dest = insertar_col_final(dest, nueva_columna(colSrc->id, colSrc->valor));
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
		colAct = filaAct->primeraCol;
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
    Columna *columna_aux=fila_aux->primeraCol;
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
    Columna *columna_aux=fila_aux->primeraCol;
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
    // Si columna_aux es NULL, esta columna será la última en la fila
    if (!columna_aux)
    	fila_aux->ultCol = nColumna;

    if (prev_col!=NULL)
    	prev_col->next=nColumna;
    else
    	fila_aux->primeraCol = nColumna;
    return matrizP;

  }
  // Si no encuentra el id crea la fila y la columna
  Fila *nFila = nueva_fila(i);
  Columna *nColumna = nueva_columna(j,elemento);
  nFila->primeraCol=nColumna;
  nFila->ultCol=nColumna;
  nFila->next=fila_aux;

  if (prev_fila!=NULL)
  	prev_fila->next=nFila;
  else
  	matrizP->filas = nFila;
  
  return matrizP;
}


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
	Columna *c1, *c2, *minCol;

	 	while (f1 != NULL && f2 != NULL) {
		// Crear fila
		idFilaAct = MIN(f1->id, f2->id);
		if (fSum->primeraCol != NULL) {
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
			c1 = f1->primeraCol;
			c2 = f2->primeraCol;
			while (c1 != NULL && c2 != NULL) {
				// La lógica de las comparaciones es similar a la de las filas
				minCol = MIN_COL(c1, c2);
				if (c1->id != c2->id) {
					fSum = insertar_col_final(fSum, nueva_columna(minCol->id, minCol->valor));
					if(minCol == c1)
						c1 = c1->next;
					else
						c2 = c2->next;
				}
				else {
					// No se debe agregar la columna si los elementos suman 0
					int sumaCols = c1->valor + c2->valor;
					if (sumaCols)
						fSum = insertar_col_final(fSum, nueva_columna(c1->id, sumaCols));
					c1 = c1->next;
					c2 = c2->next;
				}
			}
			// Agregar columnas sobrantes
			while (c1) {
				fSum = insertar_col_final(fSum, nueva_columna(c1->id, c1->valor));
				c1 = c1->next;
			}
			while (c2) {
				fSum = insertar_col_final(fSum, nueva_columna(c2->id, c2->valor));
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


// Transponer una matriz -> Devuelve un puntero a una nueva matriz conteniendo la transpuesta
Matriz *transponer(const Matriz *matrizP) {
	if (!matrizP) {
		fprintf(stderr, "No se puede transponer una matriz nula\n");
		exit(1);
	}

	Matriz *mTrans = nueva_matriz(matrizP->numColumnas, matrizP->numFilas);
	Fila *filaAct, *filaPrev, *filaAux;
	Columna *colAct;
	register int idCol;
	// Para cada fila de la matriz original
	for (filaAct = matrizP->filas; filaAct != NULL; filaAct = filaAct->next)
		// Para cada columna de esta fila
		for (colAct = filaAct->primeraCol; colAct != NULL; colAct = colAct->next) {
			idCol = colAct->id;
			// Buscar en la transpuesta la fila correspondiente al id de la columna
			filaPrev = NULL;
			for (filaAux = mTrans->filas; filaAux != NULL && filaAux->id <= idCol; filaAux = filaAux->next)
				filaPrev = filaAux;
			// Si se consiguió la fila, quedará en filaPrev
			// Entonces, se inserta al final la columna correspondiente
			if (filaPrev && filaPrev->id == idCol)
				filaPrev = insertar_col_final(filaPrev, nueva_columna(filaAct->id, colAct->valor));

			// Si no se consiguió la fila, crearla entre filaPrev y filaAux
			else {
				Fila *nFila = nueva_fila(idCol);
				if (filaPrev)
					filaPrev->next = nFila;
				else
					mTrans->filas = nFila;
				nFila->next = filaAux;
				nFila = insertar_col_final(nFila, nueva_columna(filaAct->id, colAct->valor));
			}
		}

	return mTrans;
}


// Multiplica m1 y m2 y devuelve un apuntador a la matriz producto
Matriz *multiplicar_matrices(const Matriz *m1, const Matriz *m2) {
	if (!m1 || !m2) {
		fprintf(stderr, "No se pueden multiplicar matrices si alguna es nula\n");
		exit(1);
	}
	if (m1->numColumnas != m2->numFilas) {
		fprintf(stderr, "La primera matriz debe tener tantas columnas como filas tenga la segunda\n");
		exit(1);
	}

	// Se usa la transpuesta de m2 para acceso rápido por filas
	Matriz *transM2 = transponer(m2);

	Matriz *mult = nueva_matriz(m1->numFilas, m2->numColumnas);
	mult->filas = nueva_fila(m1->filas->id);
	Fila *filaM1, *filaM2, *fProd = mult->filas;
	Columna *colM1, *colM2;
	register int prod;
	// Para cada fila en m1
	for (filaM1 = m1->filas; filaM1 != NULL; filaM1 = filaM1->next) {
		if (!fProd->primeraCol)
			fProd->id = filaM1->id;
		else {
			fProd->next = nueva_fila(filaM1->id);
			fProd = fProd->next;
		}
		// Para cada fila en transM2
		for (filaM2 = transM2->filas; filaM2 != NULL; filaM2 = filaM2->next) {
			colM1 = filaM1->primeraCol;
			colM2 = filaM2->primeraCol;
			prod = 0;
			while (colM1 && colM2) {
				if (colM1->id < colM2->id) 
					colM1 = colM1->next;
				else if (colM2->id < colM1->id)
					colM2 = colM2->next;
				else {
					prod += colM2->valor * colM1->valor;
					colM1 = colM1->next;
					colM2 = colM2->next;
				}
			}
			if (prod)
				fProd = insertar_col_final(fProd, nueva_columna(filaM2->id, prod));
		}
	}

	limpiar_matriz(transM2);
	return mult;
}