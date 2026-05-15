#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "comun.h"

int llega10 = 0;

// Prototipar funciones
void R10(int signal);
void RNOGRAF(int signal);
int creaproceso(const char nombre[], const char redire[]);

int main()
{

    int maxestudiantes = 15; // Estudiantes a generar y esperar

    int creamin = 1;
    int creamax = 3; // tiempos de creación, limites

    // Preparar handlers de 10 y 12
    signal(10, R10);
    signal(12, RNOGRAF);

    // Inicializar semilla
    srand(getpid());

    // Lanzar servidor gráfico
    int pservidorgraf = creaproceso("servidor_ncurses", NULL);

    // Esperamos el OK del servidor gráfico con la señal 10

    if (!llega10)
        pause();
    llega10 = 0;

    // Lanzar ateoria para que pinte estudiantes
    for (int i = 0; i < maxestudiantes; i++)
    {
        if (rand() % 2 == 0)
        {

            creaproceso("ateoria", NULL);
        }

        else
        {

            creaproceso("atodo", NULL);
        }

        sleep(rand() % (creamax - creamin + 1) + creamin);
    }

    // Esperar los waits
    for (int i = 0; i < maxestudiantes; i++)
    {
        wait(NULL);
    }

    // Comprobar funcionamiento del servidor grafico durante 10 segundos
    sleep(10);

    // Apagar servidor gráfico, fin de ejecución
    if (kill(pservidorgraf, 12) == -1)
        perror("Error al apagar servidor gráfico");

    return 0;
}

void R10(int signal) { llega10 = 1; }
void RNOGRAF(int signal)
{
    printf("Imposible arrancar el servidor grafico\n");
    exit(-1);
}
int creaproceso(const char nombre[], const char redire[]) // FUnción para lanzar procesos
{
    // Lanzar el servidor ncurses

    int vpid = fork();

    if (vpid == 0)
    {
        // redireccionar salida estandar (1) al fichero
        if (redire != NULL)
        {
            close(1);
            open(redire, O_WRONLY | O_CREAT, O_APPEND, 0600);
        }

        execl(nombre, nombre, NULL);
        perror("Error de execl");
        exit(-1);
    }
    else if (vpid == -1)
    {
        perror("Error de fork");
        exit(-1);
    }

    return vpid;
}
