#include <stdio.h>
#include "funciones.h"

int main(){
    int opc;
    do{
        printf("Resolver ecuaciones de segundo grado\n");
        printf("==================\n");
        printf("1.Leer Coeficientes\n");
        printf("2. Visualizar ecuacion\n");
        printf("3. Calcular Raíces\n");
        printf("4. Salir\n");
        printf("Introduzca opcion: \n");
        scanf("%d",&opc);

        switch (opc)
        {
        case 1:
            leerDatos();
            break;
        case 2:
            visualizarEcuacion();
            break;
        case 3:
            calcularRaices();
            break;
        case 4: printf("Saliendo del programa...\n");
                break;
        default:
            break;
        }
    }while(opc!=4);

    return 0;
}