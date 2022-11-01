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

	do{
        system("clear");
        printf("1.Obtener elemento\n2.Asignar elemento\n3.Sumar\n4.Producto por escalar\n5.Producto de matrices\n6.Transponer matriz\n7.Crear e imprimir matriz\n");
        scanf("%d",&opc);

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
        }

	}
	while(opc!=9);
	return 0;
}

Matriz *modo_rellenar(){
    char modo;
    char archivo[100];

    printf("Ingrese el modo de creacion de matriz. 'f' por archivos, 'c' por consola\n");
    scanf("%s",&modo);
    while (modo!='c' && modo!='f'){
        printf("Modo invalido,'f' por archivos, 'c' por consola\n ");
        scanf("%s",&modo);
    }

    Matriz *m=NULL;
    if (modo=='f'){
        printf("Ingrese el archivo\n");
        scanf("%s",archivo);
        FILE* fp=fopen(archivo,"r");
        if (!fp){
           m=rellenar_matriz(fp,modo);
           fclose(fp);
        }
        return m;
    }

    if (modo=='c'){
        m=rellenar_matriz(stdin, modo);
        return m;
    }
    return m;
}

void imprimir_resultado(Matriz* matrizp){
    char modo='0';
    char archivo[100];

    printf("Ingrese el modo de impresion de resultados. 'f' por archivos, 'c' por consola\n");
    scanf("%c",&modo);
    while (modo!='c' || modo!='f'){
        printf("Modo invalido,'f' por archivos, 'c' por consola\n ");
        scanf("%c",&modo);
    }

    if (modo=='f'){
        printf("Ingrese el nombre del archivo para crearlo\n");
        scanf("%s",archivo);
        FILE* fp=fopen(archivo,"w");
        imprimir_matriz(matrizp,fp);
        fclose(fp);
        printf("Se guardo el resultado en %s",archivo);
        getchar();
        getchar();
        return;
    }

    if (modo=='c'){
        printf("Matriz resultante:\n");
        imprimir_matriz(matrizp,stdout);
        getchar();
        getchar();
        return;
    }

}

void obtener(){
    int  i,j;
    double obt;

    printf("Matriz:\n");
    Matriz *m1=modo_rellenar();
    printf("Ingrese la ubicacion del elemento a obtener\n");
    scanf("%i %i",&i,&j);
    obt=obt_elemento(i,j,m1);

    if(obt)
    printf("El elemento en %i %i es %lf\n",i,j,obt);
    getchar();
    getchar();
    limpiar_matriz(m1);
    return;
}

void asignar(){
    int  i,j;
    double elemento;

    printf("Matriz:\n");
    Matriz *m1=modo_rellenar();
    printf("Ingrese la ubicacion del elemento a asignar:\n");
    scanf("%i %i",&i,&j);
    printf("Ingrese el valor: ");
    scanf("%lf",&elemento);
    m1=asignar_elemento(i,j,elemento,m1);

    imprimir_resultado(m1);
    return;
}



void suma(){
    printf("Matriz 1:\n");
    Matriz *m1=modo_rellenar();
    printf("Matriz 2:\n");
    Matriz *m2=modo_rellenar();

    Matriz *sum=sumar(m1,m2);
    imprimir_resultado(sum);

    limpiar_matriz(m1);
    limpiar_matriz(m2);
    limpiar_matriz(sum);
    return;
}

void escalar_producto(){
    double e;

    printf("Matriz 1:\n");
    Matriz *m1=modo_rellenar();
    printf("Escalar: ");
    scanf("%lf",&e);

    m1=escalar_matriz(m1,e);

    imprimir_resultado(m1);
    return;
}

void producto(){
    printf("Matriz 1:\n");
    Matriz *m1=modo_rellenar();
    printf("Matriz 2:\n");
    Matriz *m2=modo_rellenar();

    Matriz *mult;
    mult=multiplicar_matrices(m1,m2);
    imprimir_resultado(mult);

    limpiar_matriz(m1);
    limpiar_matriz(m2);
    limpiar_matriz(mult);
    return;
}

void transp(){
    printf("Matriz :\n");
    Matriz *m1=modo_rellenar();

    Matriz *mtrans=transponer(m1);
    imprimir_resultado(mtrans);
    return;
}

void rellenar_imprimir(){
    printf("Matriz :\n");
    Matriz *m1=modo_rellenar();
    imprimir_resultado(m1);
    return;
}


