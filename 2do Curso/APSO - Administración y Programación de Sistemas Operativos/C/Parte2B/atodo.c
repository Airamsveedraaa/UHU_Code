#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <signal.h>
#include <fcntl.h>

#include "comun.h"
#include "comunestudiante.h"

extern int llega12; // Indica que ya está definida, en este caso en comun.c
extern int llega14; // Indica que ya está definida, en este caso en comun.c

/********************
 * FUNCION: main
 ********************/
int main()
{

    struct Parametros param;
    int testigo = 1;

    srand(getpid()); // inicializamos la semilla del generador de numeros aleatorios
    signal(10, R10); // me preparo para la senyal 10, que llega cuando el servidor_ncurses me pinta correctamente
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
    mensaje_espera.tipo = TIPOTODO;

    // abrimos fifos
    int ffifotodo = open("fifotodo", O_RDWR);

    // Leemos de la pipe los par�metros
    read(2, &param, sizeof(param));

    // recuperamos la salida de errores
    int lapipe = dup(2);
    close(2);
    open("/dev/tty", O_RDWR);

    // nos visualizamos en la cola de llegada
    visualiza(colagrafica, VCOLALLEGAR, PINTAR, TIPOTODO, cabeza, cuerpo);

    // Programar alarma de aburrimiento
    alarm(rand() % (param.mevoymax - param.mevoymin + 1) + param.mevoymin);

    // envio mensaje a la cola de espera
    msgsnd(colaespera, (struct tipo_espera *)&mensaje_espera, sizeof(struct tipo_espera) - sizeof(long), 0);

    // espero que me avisen con la señal 12 para pasar al profesor de todo
    if (!llega12)
        pause();

    if (llega14)
    {
        // si llega la 14, me voy de la cola y me quedo en la cola de aburrimiento
        visualiza(colagrafica, VCOLALLEGAR, BORRAR, TIPOTODO, cabeza, cuerpo);
        visualiza(colagrafica, VABURRIDO, PINTAR, TIPOTODO, cabeza, cuerpo);

        // a pesar de no estar debo esperar a que me avisen para devover el testigo esperando la señal 12 otra vez
        if (!llega12)
            pause();
        llega12 = 0;

        // devolver el testigo para que el profesor siga sin espera.
        write(ffifotodo, &testigo, sizeof(testigo));
    }

    else
    { // ha llegado la 12
        llega12 = 0;
        alarm(0); // apagar alarma

        // me borro de la cola de llegada y me pinto con el profesor de todo
        visualiza(colagrafica, VCOLALLEGAR, BORRAR, TIPOTODO, cabeza, cuerpo);
        visualiza(colagrafica, VCONTODO, PINTAR, TIPOTODO, cabeza, cuerpo);
        // estoy revisando un tiempo aleatorio entre el minimo y el máximo
        sleep((rand() % (param.revmax - param.revmin + 1)) + param.revmin);
        // me borro del profesor de todo y me pinto en la fila de finalizados
        visualiza(colagrafica, VCONTODO, BORRAR, TIPOTODO, cabeza, cuerpo);
        visualiza(colagrafica, VFINREV, PINTAR, TIPOTODO, cabeza, cuerpo);
        // devuelvo el testigo a la fifo de todo para que el profesor atienda al siguiente
        write(ffifotodo, &testigo, sizeof(testigo));
    }
    // cierro la fifo antes de terminar
    close(ffifotodo);
}
