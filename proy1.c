#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(void) {
	Matriz *m = rellenar_matriz();
	Matriz *t = transponer(m);
	imprimir_matriz(m);
	imprimir_matriz(t);
	limpiar_matriz(m);
	limpiar_matriz(t);
	return 0;
}
