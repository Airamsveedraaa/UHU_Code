#include <unistd.h>
#include <sys/msg.h>

#include "comun.h"
#include "comunestudiante.h"

int llega10 = 0; // variable que controla la llegada de la señal 10
int llega14 = 0; //variable que controla la llegada de la señal 14

/***********
 * FUNCION: visualiza
 * PARAMETRO: cola: es el id de la cola al que envia el mensaje
 * PARAMETRO: donde: ventana en la que se pinta, según definiciones de comun.h
 * PARAMETRO: que: operacion que se realiza  PINTAR o BORRAR
 * PARAMETRO: tipo: tipo del elemento que se pinta según definiciones de comun.h
 * PARAMETRO: cabeza: aspecto de la cabeza, número entre 0 y MAXCABEZAS-1
 * PARAMETRO: cuerpo: aspecto del cuerpo, número entre 0 y MAXCUERPOS-1
 * Pinta o borra en el servidor grafico segun los parametros pasados
 ****************/
void visualiza(int cola, int donde, int que, int tipo, int cabeza, int cuerpo)
{
	struct tipo_elemento peticion;

	peticion.tipo = 1; // da igual cual poner, no usamos tipos
	peticion.pid = getpid();
	peticion.donde = donde;
	peticion.que = que;
	peticion.cualidad = tipo;
	peticion.cabeza = cabeza;
	peticion.cuerpo = cuerpo;

	msgsnd(cola, (struct tipo_elemento *)&peticion, sizeof(struct tipo_elemento) - sizeof(long), 0);

	if (que == PINTAR) // Al enviar la operacion pintar hay que esperar las señal 10, que indica que todo va bien
	{
		if (!llega10)
			pause(); // espero conformidad de que me han pintado, sino me mataran
		llega10 = 0;
	}
}

/*******************
 * FUNCION: R10
 * Es invocada cuando llega la señal 10
 *******************/
void R10(int signal)
{
	llega10 = 1;
}

/*******************
 * FUNCION: R14
 * Es invocada cuando llega la señal 14
 *******************/
void R14(int signal) { llega14 = 1; };
