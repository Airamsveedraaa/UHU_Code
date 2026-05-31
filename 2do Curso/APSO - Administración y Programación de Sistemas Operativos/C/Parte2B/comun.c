#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

int llega12 = 0; // variable que controla la llegada de la señal 12

/***********
 * FUNCION: crea_cola
 * PARAMETRO: clave: es la clave devuelta por ftok para crear la cola
 * Obtiene acceso a la cola de mensajes con la clave que se le pasa
 * DEVUELVE: el idenficador de la cola creada
 ****************/
int crea_cola(key_t clave)
{
  int identificador;
  if (clave == (key_t)-1)
  {
    printf("Error al obtener clave para cola mensajes\n");
    exit(-1);
  }

  identificador = msgget(clave, 0600 | IPC_CREAT);
  if (identificador == -1)
  {
    printf("Error al obtener identificador para cola mensajes\n");
    perror("msgget");
    exit(-1);
  }

  return identificador;
}

/*******************
 * FUNCION: R12
 * Es invocada cuando llega la señal 12
 *******************/
void R12() 
{
	llega12 = 1;
}
