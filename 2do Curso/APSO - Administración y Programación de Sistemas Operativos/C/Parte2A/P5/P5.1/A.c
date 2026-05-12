#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(){


    printf("Soy el proceso A con pid %d\n",getpid());


    int tubo[2];

    pipe(tubo);

    int pidb=fork();

    if(pidb==0){

        close(2);
        dup(tubo[0]);
        execl("B","B",NULL);
        perror("A: Error en execl de B");
        exit(-1);

    }else if(pidb==-1)perror("A: Error de Fork en B");


     int pidc=fork();

    if(pidc==0){

        execl("C","C",NULL);
        perror("A: Error en execl de C");
        exit(-1);
    }else if(pidc==-1)perror("A: Error de Fork en C");

    close(tubo[0]);
    if(write(tubo[1],&pidc,sizeof(int))==-1)perror("A: Error al escribir en la PIPE");
    close(tubo[1]);


    sleep(1);
    printf("A: Primer mensaje\n");
    if(kill(pidb,10)==-1)perror("A: Error en kill a B");



    wait(NULL);
    wait(NULL);

    printf("A: Ultimo mensaje\n");
    printf("Fin de proceso A\n");

    return 0;
}