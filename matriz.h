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
	// Apuntadores a la primera y última columna
	Columna *primeraCol, *ultCol;
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


// Funciones de creación y liberación de matrices
Matriz *nueva_matriz(int nFilas, int nCols);
Fila *nueva_fila(int id);
Columna *nueva_columna(int id, int val);
Matriz *rellenar_matriz(FILE *fp, char modo);
void limpiar_matriz(Matriz *matrizP);

// Utilidades
Fila *copiar_fila(Fila *src, Fila *dest);
Fila *insertar_col_final(Fila *filaP, Columna *nuevaC);

// Funciones básicas
void imprimir_matriz(Matriz *matrizP, FILE *fp);
int obt_elemento(int i, int j, Matriz *matrizP);
Matriz *asignar_elemento(int i, int j, int elemento, Matriz *matrizP);

// Funciones de aritmética de matrices
Matriz *sumar(const Matriz *m1, const Matriz *m2);
Matriz *transponer(const Matriz *matrizP);
Matriz *multiplicar_matrices(const Matriz *m1, const Matriz *m2);
Matriz *escalar_matriz(Matriz *matrizP,int escalar);
