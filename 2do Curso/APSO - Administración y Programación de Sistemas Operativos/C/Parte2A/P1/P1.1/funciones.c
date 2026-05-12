#include "funciones.h"

int x, y, z;

void leerDatos()
{

    printf("Dame los 3 coeficientes de la ecuación en orden (cuadratico, lineal, constante)\n");
    scanf("%d %d %d", &x, &y, &z);
}

void visualizarEcuacion()
{

    printf("La ultima ecuacion introducida es: %dx²,%dx,%d\n", x, y, z);
}

void calcularRaices()
{

    int discriminante = (y * y) - (4 * x * z);

    if (discriminante < 0)
    {
        printf("No hay raíces reales\n");
    }

    else if (discriminante == 0)
    {
        double raiz = -y / (2 * x);
        printf("Hay una raíz doble %f\n", raiz);
    }
    else
    {
        double ecuacion1 = (-y + sqrt(discriminante)) / (2 * x);
        double ecuacion2 = (-y - sqrt(discriminante)) / (2 * x);

        printf("Raíz 1: %f\n", ecuacion1);
        printf("Raíz 2: %f\n", ecuacion2);
    }
}