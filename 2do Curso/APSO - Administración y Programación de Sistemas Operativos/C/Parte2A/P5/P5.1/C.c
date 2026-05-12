#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int llega12=0,llega14=0;

void R12(int signal){


    llega12=1;
}

void R14(int signal){

    llega14=1;
}



int main(){

    signal(12,R12);
    signal(14,R14);

    if(!llega12)pause();
    llega12=0;

    int fifo=open("FIFOBC", O_RDONLY);
    if(fifo==-1)perror("C: Error al abrir la FIFO para leer");

    int pidB;
    if(read(fifo, &pidB,sizeof(int))==-1)perror("C: Error al leer de la FIFO");
    printf("Soy el proceso C con pid %d y mi padre es el proceso con pid %d\n",getpid(),getppid());

    printf("C: Tercer Mensaje\n");
    alarm(3);
    while(!llega14){
        printf("C: Esperando Alarma...\n");
        sleep(1);
    }
    llega14=0;
    printf("C: Cuarto Mensaje\n");

    if(kill(pidB,12)==-1)perror("C: Error al hacer kill a B");
    
    printf("Fin de proceso C\n");
    close(fifo);

    return 0;
}