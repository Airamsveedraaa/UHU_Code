#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int llega10=0,llega12=0;

void R10(int signal){
    llega10=1;
}

void R12(int signal){
    llega12=1;
}


int main(){

    srand(getpid());
    signal(10,R10);
    signal(12,R12);

    printf("Soy el proceso C con pid %d y mi padre tiene pid %d\n",getpid(),getppid());

    int fifo=open("FIFOAC",O_WRONLY);
    if(fifo==-1)perror("C: Error al abrir la FIFO");

    for(int i=0;i<5;i++){
        int dato=rand()% 4 +1;
        if(write(fifo,&dato,sizeof(int))==-1)perror("C: Error al escribir en la FIFO");
    }

    close(fifo);

    if(!llega10 && !llega12)pause();

    if(llega10){
        printf("C: Gano Yo\n");
        llega10=0;
    }

    if(llega12){
        printf("C: Pierdo Yo\n");
        llega12=0;
    }

    printf("Fin del proceso C\n");

    return 0;

}