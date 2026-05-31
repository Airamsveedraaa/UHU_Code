#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/msg.h>

#include "comun.h"

extern int llega12; // Indica que ya está definida, en este caso en comun.c

/********************
 * FUNCION: main
 ********************/
int main()
{
  int testigo = 1;
  int ffifoteoria, ffifotodo; // variables para abrir las fifos

  signal(12, R12); // Llegará desde revision para finalizar este proceso
  // Abrimos la fifo para leer los testigos
  ffifotodo = open("fifotodo", O_RDWR);

  // Creamos y abrimos la cola de mensajes para la cola de revision
  int colaespera = crea_cola(ftok("./fichcola.txt", 23));
  struct tipo_espera mensaje_espera;

  while (!llega12) // repetimos esto indefinidamente, el bucle se romperá al llegar la señal 12
  {
    // Recibe el mensaje mas antiguo de la cola, si no hay lo espera
    int res = msgrcv(colaespera, (struct tipo_espera *)&mensaje_espera, sizeof(struct tipo_espera) - sizeof(long), 0, 0);
    if (res != -1)
    {

      // envia la señal 12 al pid leido
      kill(mensaje_espera.pid, 12);
      // Lee el testigo enviado a la fifo, que será enviado por el estudiante cuando finalice de revisar
      read(ffifotodo, &testigo, sizeof(testigo));
    }
  }
  // cerramos las fifos
  close(ffifoteoria);
  close(ffifotodo);
  // finaliza el proceso
  exit(0);
}
