#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int pidb, pidc;
int llega10, llega12 = 0;

void usr1(int signal)
{

    llega10 = 1;
}

void usr2(int signal)
{
    llega12 = 1;
}

int main()
{

    signal(10, usr1);
    signal(12, usr2);

    printf("Proceso A creado\n");

    pidb = fork();

    if (pidb == 0)
    {

        execl("B", "B", NULL);
        perror("Error en execl");
        exit(-1);
    }
    else if (pidb == -1)
        perror("Error en fork de B");

    pidc = fork();

    if (pidc == 0)
    {

        execl("C", "C", NULL);
        perror("Error en execl");
        exit(-1);
    }
    else if (pidc == -1)
        perror("Error en fork de C");

    sleep(1);
    printf("A: Primer Mensaje\n");


    if (kill(pidb, 12) == -1)
        perror("A: Error en kill a B");


    if (!llega10)
        pause();
    llega10 = 0;


    if (kill(pidc, 10) == -1)
        perror("A: Error en kill a C");

        if(!llega12)pause();
        llega12=0;
    if(kill(pidb,12)==-1)perror("A: Error en kill a B");

    
    wait(NULL);
    wait(NULL);
    printf("A: Ultimo Mensaje\n");

    return 0;
}