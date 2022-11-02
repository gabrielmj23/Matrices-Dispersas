#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

Matriz *modo_rellenar();
void imprimir_resultado(Matriz* matrizp);
void obtener();
void asignar();
void suma();
void escalar_producto();
void producto();
void transp();
void rellenar_imprimir();

int main(void) {
	int opc=0;
	do {
    system("clear");
    printf("1.Obtener elemento\n2.Asignar elemento\n3.Sumar matrices\n4.Producto por escalar\n5.Producto de matrices\n6.Transponer matriz\n7.Crear e imprimir matriz\n8.Salir\n");
    scanf("%i",&opc);
    fflush(stdin);

    switch (opc){
      case 1:
        obtener();
        break;
      case 2:
        asignar();
        break;
      case 3:
        suma();
        break;
      case 4:
        escalar_producto();
        break;
      case 5:
        producto();
        break;
      case 6:
        transp();
        break;
      case 7:
        rellenar_imprimir();
        break;
    }
	}
	while(opc!=8);
	return 0;
}


Matriz *modo_rellenar(){
  char modo;
  char archivo[100];

  printf("Ingrese el modo de creacion de matriz. 'f' por archivos, 'c' por consola\n");
  // Limpiar buffer antes de leer
  while ((modo=getchar())!='\n' && modo!=EOF);
  scanf("%c", &modo);
  while (modo!='c' && modo!='f'){
    printf("Modo invalido,'f' por archivos, 'c' por consola\n ");
    while ((modo=getchar())!='\n' && modo!=EOF);
    modo = getchar();
  }

  Matriz *m=NULL;
  // Lectura por archivo
  if (modo=='f'){
    printf("Ingrese el archivo\n");
    scanf("%s",archivo);
    FILE* fp=fopen(archivo,"r");
    if (fp){
      m=rellenar_matriz(fp,modo);
      fclose(fp);
    }
    else {
      fprintf(stderr, "No se pudo abrir el archivo\n");
      exit(1);
    }
  }
  // Lectura por consola
  else
		m=rellenar_matriz(stdin, modo);
  return m;
}


void imprimir_resultado(Matriz* matrizp){
  char modo;
  char archivo[100];

  printf("Ingrese el modo de impresion de resultados. 'f' por archivos, 'c' por consola\n");
  while ((modo=getchar())!='\n' && modo!=EOF);
  scanf("%c",&modo);

  while (modo!='c' && modo!='f'){
    printf("Modo invalido,'f' por archivos, 'c' por consola\n ");
    while ((modo=getchar())!='\n' && modo!=EOF);
    scanf("%c",&modo);
  }

  // Escribir a un archivo
  if (modo=='f'){
    printf("Ingrese el nombre del archivo para crearlo\n");
    scanf("%s",archivo);
    FILE* fp=fopen(archivo,"w");
    if (!fp) {
    	fprintf(stderr, "No se pudo abrir el archivo\n");
    	exit(1);
    }
    imprimir_matriz(matrizp,fp);
    fclose(fp);
    printf("Se guardo el resultado en %s",archivo);
  }
  // Escribir en consola
  else{
    printf("Matriz resultante:\n");
    imprimir_matriz(matrizp,stdout);
  }
  getchar();
  getchar();
}


void obtener(){
  int i,j;

	printf("Matriz:\n");
  Matriz *m1=modo_rellenar();
  printf("Ingrese la ubicacion del elemento a obtener\n");
  scanf("%i %i",&i,&j);

  printf("El elemento en %i %i es %.3lf\n",i,j,obt_elemento(i,j,m1));
  getchar();
  getchar();
  limpiar_matriz(m1);
}


void asignar(){
  int i,j;
  double elemento;

  printf("Matriz:\n");
  Matriz *m1=modo_rellenar();
  printf("Ingrese la ubicacion del elemento a asignar:\n");
  scanf("%i %i",&i,&j);
  printf("Ingrese el valor: ");
  scanf("%lf",&elemento);
  m1=asignar_elemento(i,j,elemento,m1);

  imprimir_resultado(m1);
  getchar();
  getchar();
  limpiar_matriz(m1);
}


void suma(){
  printf("Matriz 1:\n");
  Matriz *m1=modo_rellenar();
  printf("Matriz 2:\n");
  Matriz *m2=modo_rellenar();

  Matriz *sum=sumar(m1,m2);
  imprimir_resultado(sum);
  getchar();
  getchar();

  limpiar_matriz(m1);
  limpiar_matriz(m2);
  limpiar_matriz(sum);
}

void escalar_producto(){
  double e;

  printf("Matriz 1:\n");
  Matriz *m1=modo_rellenar();
  printf("Escalar: ");
  scanf("%lf",&e);

  m1=escalar_matriz(m1,e);

  imprimir_resultado(m1);
  getchar();
  getchar();
  limpiar_matriz(m1);
}

void producto(){
  printf("Matriz 1:\n");
  Matriz *m1=modo_rellenar();
  printf("Matriz 2:\n");
  Matriz *m2=modo_rellenar();

  Matriz *mult;
  mult=multiplicar_matrices(m1,m2);
  imprimir_resultado(mult);
  getchar();
  getchar();

  limpiar_matriz(m1);
  limpiar_matriz(m2);
  limpiar_matriz(mult);
}

void transp(){
  printf("Matriz :\n");
  Matriz *m1=modo_rellenar();

  Matriz *mtrans=transponer(m1);
  imprimir_resultado(mtrans);
  getchar();
  getchar();

  limpiar_matriz(m1);
  limpiar_matriz(mtrans);
}

void rellenar_imprimir(){
  printf("Matriz :\n");
  Matriz *m1=modo_rellenar();
  imprimir_resultado(m1);
  limpiar_matriz(m1);
}