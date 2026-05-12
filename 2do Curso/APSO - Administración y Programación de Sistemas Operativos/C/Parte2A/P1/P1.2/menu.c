#include <stdio.h>
#include "funciones.h"

int main(){
    int opc;
    do{
        printf("Menú\n");
        printf("==================\n");
        printf("1.Leer Datos\n");
        printf("2. Visualizar máximo\n");
        printf("3. Calcular seno del máximo\n");
        printf("4. Salir\n");
        printf("Introduzca opcion: \n");
        scanf("%d",&opc);

        switch (opc)
        {
        case 1:
            leerDatos();
            break;
        case 2:
            visualizarMaximo();
            break;
        case 3:
            calcularSeno();
            break;
        case 4: printf("Saliendo del programa...\n");
                break;
        default:
            break;
        }
    }while(opc!=4);

    return 0;
}