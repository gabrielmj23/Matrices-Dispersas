#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(void) {
	Matriz *m1 = rellenar_matriz();
	Matriz *m2 = rellenar_matriz();
	//Matriz *m3 = rellenar_matriz();

	Matriz *s12 = sumar(m1, m2);
	//Matriz *s13 = sumar(m1, m3);
	imprimir_matriz(s12);

	limpiar_matriz(m1);
	limpiar_matriz(m2);
	//limpiar_matriz(m3);
	limpiar_matriz(s12);
	//limpiar_matriz(s13);
	return 0;
}
