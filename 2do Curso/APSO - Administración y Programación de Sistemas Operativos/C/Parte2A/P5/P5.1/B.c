#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int llega10=0,llega12=0;

void R10(int signal){
    llega10=1;
}

void R12(int signal){
    llega12=1;
}

int main(){

    
    signal(10,R10);   
    signal(12,R12);

    mkfifo("FIFOBC",0600);

    if(!llega10)pause();
    llega10=0;
    printf("Soy el proceso B con pid %d y mi padre es el proceso con pid %d\n",getpid(),getppid());
    printf("B: Segundo Mensaje\n");


    int leePipe=dup(2);
    close(2);
    if(open("/dev/tty", O_WRONLY)==-1)perror("B: Error al recuperar salida de errores");

    int pidC;

    if(read(leePipe,&pidC,sizeof(int))==-1)perror("B: Error al leer de PIPE");

    if(kill(pidC,12)==-1)perror("B: Error al hacer kill a C");

    int fifo=open("FIFOBC",O_WRONLY);
    if(fifo==-1)perror("B: Error al abrir la FIFO para escribir");

    int mipid=getpid();
    if(write(fifo, &mipid, sizeof(int))==-1)perror("B: Error al escribir en la FIFO");


    if(!llega12)pause();
    llega12=0;

    printf("B: Quinto mensaje\n");

    if(unlink("FIFOBC")==-1)perror("B: Error al cerrar");
    printf("Fin de proceso B\n");

    return 0;
}