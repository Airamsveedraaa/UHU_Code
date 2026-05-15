#include <stdio.h>
#include <sys/msg.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "comun.h"
#include "comunestudiante.h"

int main()
{
    // Código de los estudiantes que tienen que revisar todo

    // Handler de señal
    signal(10, R10);

    // Inicializar semilla
    srand(getpid());

    // Acceder a la cola del servidor gráfico con intención de pintar
    int colagrafica = creacola(ftok("./fichcola.txt", 18));

    // Enviar petición de pintarse

    int cabeza = rand() % MAXCABEZAS;
    int cuerpo = rand() % MAXCUERPOS;

    visualizar(colagrafica, VCOLALLEGAR, PINTAR, TIPOTODO, cabeza, cuerpo);

    sleep(2);

    // Enviar peticion de borrarse
    visualizar(colagrafica, VCOLALLEGAR, BORRAR, TIPOTODO, cabeza, cuerpo);

    // Pintarme en fin de revision
    visualizar(colagrafica, VABURRIDO, PINTAR, TIPOTODO, cabeza, cuerpo);

    return 0;
}