#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "comun.h"

int llega10 = 0;

// Prototipar funciones
void R10(int signal);
void R12(int signal);
void visualizar(int cola, int donde, int que, int cualidad, int cabeza, int cuerpo);

int main()
{

    // Preparar handlers de 10 y 12
    signal(10, R10);
    signal(12, R12);

    // Inicializar semilla
    srand(getpid());

    // Lanzar el servidor ncurses

    int pservidorgraf = fork();

    if (pservidorgraf == 0)
    {

        execl("servidor_ncurses", "servidor_ncurses", NULL);
        perror("Error de execl de servidor_ncurses");
        exit(-1);
    }
    else if (pservidorgraf == -1)
    {
        perror("Error de fork de servidor_ncurses");
    }

    // Esperamos el OK del servidor gráfico con la señal 10

    if (!llega10)
        pause();
    llega10 = 0;

    // Acceder a la cola del servidor gráfico con intención de pintar
    key_t clave = ftok("./fichcola.txt", 18);

    if (clave == -1)
    {
        perror("Error generar clave");
        exit(-1);
    }

    int colagrafica = msgget(clave, 0600 | IPC_CREAT);

    if (colagrafica == -1)
    {
        perror("Error generar cola");
        exit(-1);
    }

    // Enviar petición de pintarse

    int cabeza = rand() % MAXCABEZAS;
    int cuerpo = rand() % MAXCUERPOS;

    visualizar(colagrafica, VCOLALLEGAR, PINTAR, TIPOTEORIA, cabeza, cuerpo);

    sleep(2);

    // Enviar peticion de borrarse
    visualizar(colagrafica, VCOLALLEGAR, BORRAR, TIPOTEORIA, cabeza, cuerpo);

    // Enviar peticion de irme
    visualizar(colagrafica, VCONTEORIA, PINTAR, TIPOTEORIA, cabeza, cuerpo);
    sleep(2);

    // Enviar peticion de borrarse
    visualizar(colagrafica, VCONTEORIA, BORRAR, TIPOTEORIA, cabeza, cuerpo);

    // Pintarme en fin de revision
    visualizar(colagrafica, VFINREV, PINTAR, TIPOTEORIA, cabeza, cuerpo);
    sleep(2);

    // Comprobar funcionamiento del servidor grafico durante 10 segundos
    sleep(10);

    // Apagar servidor gráfico
    if (kill(pservidorgraf, 12) == -1)
        perror("Error al apagar servidor gráfico");

    return 0;
}

void R10(int signal) { llega10 = 1; }
void R12(int signal) { printf("Imposible arrancar el servidor grafico\n"); }
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