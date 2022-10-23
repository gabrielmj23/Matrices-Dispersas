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

//Obtener un elemento de la matriz
int obt_elemento(int i, int j, matriz *matrizP){
    //Revisar si la matriz existe
    if (matrizP==NULL){
        fprintf(stderr, "obt_elemento: La matriz no existe");
        exit(1);
    }
    //Revisar si la ubicacion esta en la matriz
    if (i>matrizP->numFilas || j>matrizP->numColumnas){
        fprintf(stderr, "obt_elemento: El elemento esta fuera de las dimensiones de la matriz");
        exit(1);
    }
     //Buscar la fila
     Fila *fila_aux=matrizP->filas;
    for(; fila_aux->id<i && fila_aux->id!=NULL ; fila_aux=fila_aux->next);

        //Si encuentra la fila, empieza a buscar la columna
        if (fila_aux->id==i){
            Columna *columna_aux=fila_aux->col;
            for(;columna_aux->id<j && columna_aux->id!=NULL;columna_aux=columna_aux->next);
            if(columna_aux->id==j)
                //Si encuentra la columna, devuelve el valor
                return columna_aux->valor;
            //Si no encuentra el id de la columna retorna 0
            return 0;

        }
        //Si no encuentra el id de la fila retorna 0
        return 0;

}

Matriz *asign_elemento(int i, int j, int elemento, matriz *matrizP){
    //Revisar si la matriz existe
    if (matrizP==NULL){
        fprintf(stderr, "asign_elemento: La matriz no existe");
        exit(1);
    }

    //Buscar la fila
     Fila *fila_aux=matrizP->filas;
    for(; fila_aux->id<i && fila_aux->id!=NULL ; fila_aux=fila_aux->next);

        //Si encuentra la fila, empieza a buscar la columna
        if (fila_aux->id==i){
            Columna *columna_aux=fila_aux->col;
            for(;columna_aux->id<j && columna_aux->id!=NULL;columna_aux=columna_aux->next);
            if(columna_aux->id==j){
                //Si encuentra la columna, asigna el elemento
                columna_aux->valor=elemento;
                return *matrizP;
            }
            //Si no encuentra el id de la columna la crea
            columna_aux=nueva_columna(j,elemento);
            return *matrizP;

        }
        //Si no encuentra el id crea la fila y crea la columna
        fila_aux=nueva_fila(i);
        Columna *columna_aux=fila_aux->col;
        columna_aux=nueva_columna(j,elemento);
        return *matrizP;


}
