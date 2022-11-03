/*
 * matriz.h: Contiene declaraciones de tipo de matrices, filas y columnas
 * Además contiene los prototipos de las funciones básicas de manejo de matrices
 *
 */

typedef struct columna
{
	int id;
	double valor;
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
Matriz *nueva_matriz(const int nFilas, const int nCols);
Fila *nueva_fila(const int id);
Columna *nueva_columna(const int id, const double val);
Matriz *rellenar_matriz(FILE *fp, const char modo);
void limpiar_matriz(Matriz *matrizP);

// Utilidades
Fila *copiar_fila(Fila *src, Fila *dest);
Fila *insertar_col_final(Fila *filaP, Columna *nuevaC);

// Funciones básicas
void imprimir_nodos(const Matriz *matrizP, FILE *fp);
void imprimir_matriz(const Matriz *matrizP, FILE *fp);
double obt_elemento(const int i, const int j, const Matriz *matrizP);
Matriz *asignar_elemento(const int i, const int j, const double elemento, Matriz *matrizP);

// Funciones de aritmética de matrices
Matriz *sumar_matrices(const Matriz *m1, const Matriz *m2);
Matriz *transponer(const Matriz *matrizP);
Matriz *multiplicar_matrices(const Matriz *m1, const Matriz *m2);
Matriz *escalar_matriz(Matriz *matrizP, const double escalar);
