#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>

#include "comun.h"

// CABECERAS DE LAS FUNCIONES EMPLEADAS
int creaproceso(const char *, const char *);
int creaprocesotub(const char nombre[], int tub[], int canal);
void leeparametros(struct Parametros *param, int *maxestudiantes, int *creamin, int *creamax, int ok);
void R10(int signal);
void RNOGRAF(int signal);

int llega10 = 0; // Controla la llegada de la señal 10

/********************
 * FUNCION: main
 * Puede tomar un parámetro, que será una 's' si se quiere modificar los valores de funcionamiento de la
 * práctica, si no toma ninguno o el parámetro es distinto de 's' se ejecuta con los varlores por defecto
 ********************/
int main(int argc, char *arv[])
{

	int tubo[2];
	struct Parametros param;
	int maxestudiantes, creamin, creamax;
	int testigo = 1;

	signal(10, R10); // Llegará desde el servidor gráfico si todo va bien
	signal(12, RNOGRAF); // Llegará desde el servidor gráfico si no es posible la visualización
	srand(getpid()); // Inicializa la semilla del generardor de numeros aleatorios

	// BORRAMOS LAS POSIBLES COLAS ABIERTAS DE EJECUCIONES PREVIAS
	// ACCEDEMOS A LA COLA DEL SERVIDOR GRAFICO
	int colagrafica = crea_cola(ftok("./fichcola.txt", 18));
	msgctl(colagrafica, IPC_RMID, NULL); // Borra la cola grafica
	// ACCEDEMOS A LA COLA DE REVISION
	int colaespera = crea_cola(ftok("./fichcola.txt", 23));
	msgctl(colaespera, IPC_RMID, NULL); // Borra la cola de espera

	// COMPRUEBA SI SE PASA UN PARAMETRO Y SI ES UNA s, PARA PEDIR PARAMETROS
	if ((argc > 1) && (strcmp(arv[1], "s") == 0))
		leeparametros(&param, &maxestudiantes, &creamin, &creamax, 1);
	else
		leeparametros(&param, &maxestudiantes, &creamin, &creamax, 0);

	// Lanza el proceso servidor_ncurses y espera la llegada de la señal 10, que indica que todo va bien
	int pservidorgraf = creaproceso("servidor_ncurses", NULL); // parametro 1 es proceso y parametro 2 fichero de redireccion
	if (!llega10)
		pause(); // Espero a que el servidor grafico de el OK

	// CREA LA TUBERIA DE LOS PARAMETROS Y LAS FIFOS
	pipe(tubo);
	// Borra las fifos por si se quedaron abiertas en una ejecución previa
	unlink("fifoteoria");
	unlink("fifotodo");
	// Crea las fifos
	mkfifo("fifoteoria", 0600);
	mkfifo("fifotodo", 0600);
	// Abrimos fifos para escribir testigos
	int ffifoteoria = open("fifoteoria", O_RDWR);
	int ffifotodo = open("fifotodo", O_RDWR);

	// Creamos los procesos de los profesores
	int pidprofteoria = creaproceso("profeteoria", NULL);
	int pidproftodo = creaproceso("profetodo", NULL);

	// Creamos aleatoriamente los estudiantes
	for (int i = 1; i <= maxestudiantes; i++)
	{
		if (rand() % 2 == 0)
		{
			creaprocesotub("atodo", tubo, 2);
			// Escribe los parámetros en la pipe
			write(tubo[1], &param, sizeof(param));
		}
		else
		{
			creaprocesotub("ateoria", tubo, 2);
			// Escribe los parámetros en la pipe
			write(tubo[1], &param, sizeof(param));
		}
		sleep((rand() % (creamax - creamin + 1)) + creamin);
	}
	// esperamos que terminen todos los estudiantes
	for (int i = 1; i <= maxestudiantes; i++)
		wait(NULL);

	sleep(10);
	// Envia la señal 12 al resto de procesos para que finalicen
	kill(pidprofteoria, 12);
	kill(pidproftodo, 12);
	kill(pservidorgraf, 12);
	// Cerramos las fifos
	close(ffifoteoria);
	close(ffifotodo);
	// Borramos las fifos
	unlink("fifoteoria");
	unlink("fifotodo");

	//Borramos la cola de espera
	colaespera = crea_cola(ftok("./fichcola.txt", 23));
	msgctl(colaespera, IPC_RMID, NULL); // Borra la cola de espera

	// Limpia el terminal para que no queden restos del servidor grafico
	system("reset");

}

// ************* FUNCIONES ************************************************//

/*****************
 * FUNCION: creaprocesotub
 * PARAMETRO: nombre: es la cadena de caracteres que contiene el nombre del proceso
 * PARAMETRO: tub: vector de enteros con las posiciones de la tuberia
 * PARAMETRO: canal: canal que se usará para pasar la posicion de la tuberia al proceso hijo
 * Crea el proceso llamado 'nombre' pasandole el puntero de lectura de 'tub', en la posicion 'canal'
 * DEVUELVE: el pid del proceso creado
*******************/
int creaprocesotub(const char nombre[], int tub[], int canal)
{

	int vpid;

	vpid = fork();
	if (vpid == 0)
	{
		close(canal);
		dup(tub[0]);
		execl(nombre, nombre, NULL);
		perror("error de execl");
		exit(-1);
	}
	else if (vpid == -1)
	{
		perror("error de fork");
		exit(-1);
	}
	return vpid;
}

/*****************
 * FUNCION: creaproceso
 * PARAMETRO: nombre: es la cadena de caracteres que contiene el nombre del proceso
 * PARAMETRO: redire: es la cadena de caracteres que contiene el nombre del archivo al que se redirige la salida del nuevo proceso
 * Crea el proceso llamado 'nombre' redirigiendo su salida a 'redire', salvo que éste sea NULL
 * DEVUELVE: el pid del proceso creado
*******************/
int creaproceso(const char nombre[], const char redire[])
{
	int vpid;

	vpid = fork();
	if (vpid == 0)
	{
		if (redire != NULL)
		{
			close(1);
			open(redire, O_WRONLY | O_CREAT, 0600);
		}
		execl(nombre, nombre, NULL);
		perror("error de execl");
		exit(-1);
	}
	else if (vpid == -1)
	{
		perror("error de fork");
		exit(-1);
	}
	return vpid;
}

/***************************
 * FUNCION: leeparametros
 * PARAMETRO: param: puntero a Parametros que contiene los valores de los parametros que se pasan a los procesos
 * PARAMETRO: maxestudiantes: como es por referencia, se asigna con el número de estudiantes que se crearán
 * PARAMETRO: creamin: como es por referencia, se asigna con el tiempo mínimo para crear estudiantes
 * PARAMETRO: creamax: como es por referencia, se asigna con el tiempo máximo para crear estudiantes
 * PARAMETRO: pedir: si es 1 se solicitan datos desde el teclado, si no solo se rellenan con los valores por defecto
 ***************************/
void leeparametros(struct Parametros *param, int *maxestudiantes, int *creamin, int *creamax, int pedir)
{

	*maxestudiantes = 30; // Numero de estudiantes que se crearan
	*creamin = 1;		   // Intervalo de tiempo para crear nuevos estudiantes MIN
	*creamax = 3;		   // Intervalo de tiempo para crear nuevos estudiantes MAX
	param->revmin = 5;	   // Intervalo de tiempo en revisar MIN
	param->revmax = 8;	   // Intervalo de tiempo en revisar MAX
	param->mevoymin = 15;  // Intervalo de tiempo en esperar para irse MIN
	param->mevoymax = 20;  // Intervalo de tiempo en esperar para irse MAX

	while (pedir == 1)
	{
		system("clear");
		printf("Valores de los parámetros...\n\n");
		printf("Numero de estudiantes que se crearan: %d\n", *maxestudiantes);
		printf("Intervalo de tiempo para crear nuevos estudiantes: [%d-%d] \n", *creamin, *creamax);
		printf("Intervalo de tiempo en revisar: [%d-%d]\n", param->revmin, param->revmax);
		printf("Intervalo de tiempo en esperar para irse: [%d-%d]\n", param->mevoymin, param->mevoymax);
		printf("Pulse 1 si desea introducir nuevos valores, cualquier otro valor si desea continuar.\n");
		scanf("%d", &pedir);

		if (pedir == 1)
		{
			do
			{
				printf("Numero de estudiantes que se crearan [maximo 50]:\n");
				scanf("%d", maxestudiantes);
			} while (*maxestudiantes <= 0 || *maxestudiantes > 50);

			do
			{
				printf("Intervalo de tiempo para crear nuevos estudiantes MIN [entre 1 y 10]: \n");
				scanf("%d", creamin);
			} while (*creamin < 1 || *creamin > 10);

			do
			{
				printf("Intervalo de tiempo para crear nuevos estudiantes MAX [entre 5 y 20]: \n");
				scanf("%d", creamax);
			} while (*creamax < 5 || *creamax > 20 || *creamax <= *creamin);

			do
			{
				printf("Intervalo de tiempo en revisar MIN [entre 1 y 10]: \n");
				scanf("%d", &param->revmin);
			} while (param->revmin < 1 || param->revmin > 10);

			do
			{
				printf("Intervalo de tiempo en revisar MAX [entre 5 y 20]: \n");
				scanf("%d", &param->revmax);
			} while (param->revmax < 5 || param->revmax > 20 || param->revmax <= param->revmin);

			do
			{
				printf("Intervalo de tiempo en esperar para irse MIN [entre 1 y 10]:\n");
				scanf("%d", &param->mevoymin);
			} while (param->mevoymin < 1 || param->mevoymin > 10);

			do
			{
				printf("Intervalo de tiempo en esperar para irse MAX [entre 5 y 20]:\n");
				scanf("%d", &param->mevoymax);
			} while (param->mevoymax < 5 || param->mevoymax > 20 || param->mevoymax <= param->mevoymin);
		}
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
 * FUNCION: RNOGRAF
 * Es invocada cuando llega la señal 12, finaliza el proceso porque el servidor gráfico no puede visualizar
 *******************/
void RNOGRAF(int signal)
{
	printf("No es posible arrancar el servidor gráfico\n");
	exit(-1);
}
