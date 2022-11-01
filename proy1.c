#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(void) {
	Matriz *m1 = rellenar_matriz(stdin, 'c');
	Matriz *m2 = rellenar_matriz(stdin, 'c');
	FILE *fp = fopen("matrizOut.txt", "w");
	Matriz *sm = sumar(m1, m2);
	imprimir_matriz(sm, stdout);
	fclose(fp);
	return 0;
}