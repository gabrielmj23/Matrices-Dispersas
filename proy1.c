#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(void) {
	Matriz *m = rellenar_matriz(stdin, 'c');
	FILE *fp = fopen("matrizOut.txt", "w");
	imprimir_matriz(m, fp);
	fclose(fp);
	return 0;
}