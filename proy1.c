#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(void) {
	Matriz *m1 = rellenar_matriz();
	Matriz *m2 = rellenar_matriz();
	imprimir_matriz(m1);
	imprimir_matriz(m2);
	Matriz* mult = multiplicar_matrices(m1, m2);
	imprimir_matriz(mult);
	limpiar_matriz(m1);
	limpiar_matriz(m2);
	limpiar_matriz(mult);
	return 0;
}
