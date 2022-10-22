/*
 * matriz.h: Contiene declaraciones de tipo de matrices, filas y columnas
 * Además contiene los prototipos de las funciones básicas de manejo de matrices
 *
 */

typedef struct columna 
{
	int id;
	int valor;
	struct columna *next;
}
Columna;


typedef struct fila 
{
	int id;
	Columna *col;
	struct fila *next;
}
Fila;


typedef struct matriz
{
	int numFilas;
	int numColumnas;
	Fila *filas;
}
Matriz;


Matriz *nueva_matriz(int nFilas, int nCols);
Fila *nueva_fila(int id);
Columna *nueva_columna(int id, int val);
Fila *copiar_fila(Fila *src, Fila *dest);
void imprimir_matriz(Matriz *matrizP);