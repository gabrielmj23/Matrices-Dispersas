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

Matriz *modo_rellenar(){
    char modo='0';
    char archivo[100];

    printf("Ingrese el modo de creacion de matriz. 'f' por archivos, 'c' por consola\n");
    scanf("%c",&modo);
    while (modo!='c' || modo!='f'){
        printf("Modo invalido,'f' por archivos, 'c' por consola\n ");
        scanf("%c",&modo);
    }

    Matriz *m;
    if (modo=='f'){
        printf("Ingrese el archivo\n");
        scanf("%s",&archivo);
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
        scanf("%s",&archivo);
        FILE* fp=fopen(archivo,"w");
        imprimir_matriz(matrizp,fp);
        fclose(fp);
        return;
    }

    if (modo=='c'){
        printf("Matriz resultante:\n");
        imprimir_matriz(matrizp,stdout);
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
    printf("El elemento en %i %i es %lf",i,j,obt);

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
    scanf("%lf",&elemento)
    m1=asignar_elemento(i,j,elemento,m1);

    imprimir_resultado(m1);
    return;
}

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

void producto_es(){
    double e;

    printf("Matriz 1:\n");
    Matriz *m1=modo_rellenar();
    printf("Escalar: ");
    scanf("%i",&e);

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
    limpiar_matriz(mult)
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


