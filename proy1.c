#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(void) {
	FILE *fp = fopen("matriz.txt", "r");
	Matriz *m = rellenar_matriz(fp, 'f');
	fclose(fp);
	imprimir_matriz(m);
	return 0;
}