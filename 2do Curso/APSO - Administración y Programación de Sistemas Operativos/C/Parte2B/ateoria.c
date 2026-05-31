#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <signal.h>
#include <fcntl.h>

#include "comun.h"
#include "comunestudiante.h"

extern int llega12; // Indica que ya está definida, en este caso en comun.c
extern int llega14; // Indica que ya está definida, en este caso en comun.c
int llega18 = 0;    // Controla la llegada de la señal 18

/*******************
 * FUNCION: R18
 * Es invocada cuando llega la señal 18
 *******************/
void R18(int signal)
{
    llega18 = 1;
}

/********************
 * FUNCION: main
 ********************/
int main()
{

    struct Parametros param;
    int testigo = 1;

    srand(getpid()); // inicializamos la semilla del generador de numeros aleatorios
    signal(10, R10); // me preparo para la senyal 10, que llega cuando el servidor_ncurses me pinta correctamente
    signal(18, R18); // me preparo para la senyal 18, que llega desde el profesor de teoría para que pase
    signal(12, R12); // me preparo para la senyal 12, que llega desde el profesor de todo para que pase
    signal(14, R14); // me preparo para la señal 14, que llega con la alarma

    // Generamos aleatoriamente la apariencia de la cabeza y el cuerpo
    int cabeza = rand() % MAXCABEZAS;
    int cuerpo = rand() % MAXCUERPOS;

    // Creamos y abrimos la cola de mensajes para el servidor grafico
    int colagrafica = crea_cola(ftok("./fichcola.txt", 18));

    // Creamos y abrimos la cola de mensajes para la cola de revision
    int colaespera = crea_cola(ftok("./fichcola.txt", 23));

    // Creamos el mensaje, con nuestro tipo y pid
    struct tipo_espera mensaje_espera;
    mensaje_espera.pid = getpid();
    mensaje_espera.tipo = TIPOTEORIA;

    // abrimos fifos
    int ffifotodo = open("fifotodo", O_RDWR);
    int ffifoteoria = open("fifoteoria", O_RDWR);

    // Leemos de la pipe los par�metros
    read(2, &param, sizeof(param));

    // recuperamos la salida de errores
    int lapipe = dup(2);
    close(2);
    open("/dev/tty", O_RDWR);

    // nos visualizamos en la cola de llegada
    visualiza(colagrafica, VCOLALLEGAR, PINTAR, TIPOTEORIA, cabeza, cuerpo);

    // programa la alarma de aburrimiento entra minimo y maximo
    alarm(rand() % (param.mevoymax - param.mevoymin + 1) + param.mevoymin);

    // envio mensaje a la cola de espera
    msgsnd(colaespera, (struct tipo_espera *)&mensaje_espera, sizeof(struct tipo_espera) - sizeof(long), 0);

    // espero que me avisen con la señal 12 para pasar al profesor de todo o la 18 para pasar al de teoria
    if (!llega12 && !llega18)
        pause();

    if (llega14)
    {
        // me borro de la cola de espera y me voy a aburrido
        visualiza(colagrafica, VCOLALLEGAR, BORRAR, TIPOTEORIA, cabeza, cuerpo);
        visualiza(colagrafica, VABURRIDO, PINTAR, TIPOTEORIA, cabeza, cuerpo);

        // a pesar de que no estoy , espero las señales 12 o 18 y aviso al profesor correspondiente
        if (!llega12 && !llega18)
            pause();

        if (llega12)
        { //llega la 12, aviso al profesor de todo
            llega12 = 0;
            write(ffifotodo, &testigo, sizeof(testigo));
        }
        else
        { //llega 18, aviso al de teoria
            llega18 = 0;
            write(ffifoteoria, &testigo, sizeof(testigo));
        }
    }

    else
    {
        alarm(0); // desactivar la alarma

        if (llega18) // me ha avisado el profesor de teoria
        {
            llega18 = 0;
            // me borro de la cola de llegada y me pinto con el profesor de teoria
            visualiza(colagrafica, VCOLALLEGAR, BORRAR, TIPOTEORIA, cabeza, cuerpo);
            visualiza(colagrafica, VCONTEORIA, PINTAR, TIPOTEORIA, cabeza, cuerpo);
            // estoy revisando un tiempo aleatorio entre el minimo y el máximo
            sleep((rand() % (param.revmax - param.revmin + 1)) + param.revmin);
            // me borro del profesor de teoria y me pinto en la fila de finalizados
            visualiza(colagrafica, VCONTEORIA, BORRAR, TIPOTEORIA, cabeza, cuerpo);
            visualiza(colagrafica, VFINREV, PINTAR, TIPOTEORIA, cabeza, cuerpo);
            // devuelvo el testigo a la fifo de teoria para que el profesor atienda al siguiente
            write(ffifoteoria, &testigo, sizeof(testigo));
        }
        else // me ha avisado el profesor de todo
        {
            llega12 = 0;
            // me borro de la cola de llegada y me pinto con el profesor de todo
            visualiza(colagrafica, VCOLALLEGAR, BORRAR, TIPOTEORIA, cabeza, cuerpo);
            visualiza(colagrafica, VCONTODO, PINTAR, TIPOTEORIA, cabeza, cuerpo);
            // estoy revisando un tiempo aleatorio entre el minimo y el máximo
            sleep((rand() % (param.revmax - param.revmin + 1)) + param.revmin);
            // me borro del profesor de todo y me pinto en la fila de finalizados
            visualiza(colagrafica, VCONTODO, BORRAR, TIPOTEORIA, cabeza, cuerpo);
            visualiza(colagrafica, VFINREV, PINTAR, TIPOTEORIA, cabeza, cuerpo);
            // devuelvo el testigo a la fifo de todo para que el profesor atienda al siguiente
            write(ffifotodo, &testigo, sizeof(testigo));
        }
    }
    // cierro las fifos antes de terminar
    close(ffifoteoria);
    close(ffifotodo);
}
