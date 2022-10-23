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
int obt_elemento(int i, int j, Matriz *matrizP);
Matriz *asign_elemento(int i, int j, int elemento, Matriz *matrizP);

