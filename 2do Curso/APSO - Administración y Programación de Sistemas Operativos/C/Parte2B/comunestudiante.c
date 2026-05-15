#include "comunestudiante.h"

int llega10=0;
// Método para operaciones de pintado, si pinta espera la 10, si borra no
void visualizar(int cola, int donde, int que, int cualidad, int cabeza, int cuerpo)
{
    struct tipo_elemento peticion;
    peticion.tipo = 1;
    peticion.pid = getpid();
    peticion.donde = donde;
    peticion.que = que;
    peticion.cualidad = cualidad;
    peticion.cabeza = cabeza;
    peticion.cuerpo = cuerpo;

    if (msgsnd(cola, &peticion, sizeof(peticion) - sizeof(long), 0) == -1)
        perror("Error al escribir");

    if (que == PINTAR)
    {
        if (!llega10)
            pause();
        llega10 = 0;
    }
}

void R10(int signal) { llega10 = 1; };
