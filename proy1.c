#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(void) {
	Matriz *m1 = rellenar_matriz();
	imprimir_matriz(m1);
	m1 = escalar_matriz(m1, -2);
	imprimir_matriz(m1);
	limpiar_matriz(m1);
	return 0;
}
