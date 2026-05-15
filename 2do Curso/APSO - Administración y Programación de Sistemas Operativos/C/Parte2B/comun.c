#include "comun.h"
#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>

//Metodo para crear colas
int creacola(key_t clave)
{

    if (clave == -1)
    {
        perror("Error generar clave");
        exit(-1);
    }

    int cola = msgget(clave, 0600 | IPC_CREAT);

    if (cola == -1)
    {
        perror("Error generar cola");
        exit(-1);
    }

    return cola;
}