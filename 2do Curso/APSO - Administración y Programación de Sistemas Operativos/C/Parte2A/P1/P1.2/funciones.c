#include "funciones.h"

int datos[10];
int maximo=-9999;

void leerDatos(){
    int i=0;
    int j;
    do{
        printf("Dame dato \n");
        scanf("%d",&j);
        datos[i]=j;
        i++;
    }while(j!=-1 && i<10);
}

void visualizarMaximo(){

    if(datos[0]==NULL){
        printf("No hay datos\n");
    }
    else{

        for(int i=0;i<10;i++){
            if(datos[i] > maximo){
                maximo=datos[i];
            }
        }
        printf("El maximo valor introducido ha sido: %d\n", maximo);
    }
}


void calcularSeno(){
    double seno=sin(maximo);

    printf("El seno del máximo es %f\n",seno);
}