#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int llega=-1;
void R10(int signal){

    if(llega==-1)llega=1;
}


void R14(int signal){

    if(llega==-1)llega=0;
}

void R12(int signal){

    if(llega==-1)llega=2;
}

int main(){

    srand(getpid());
    signal(10,R10);
    signal(14,R14);
    signal(12,R12);

    printf("Soy el proceso B con pid %d y mi padre tiene pid %d\n", getpid(),getppid());

    int pidc=fork();

    if(pidc==0){

        execl("C","C",NULL);
        perror("Error en execl");
    }else if(pidc==-1)perror("Error en fork de C");

    sleep(1);

    if(kill(getppid(),10)==-1)perror("B: Error en kill a A");

    if(kill(pidc,12)==-1)perror("B: Error en kill a C");


    int n= rand() % 3 +3;
    printf("B: Voy a programar una alarma de %d segundos\n",n);
    alarm(n);
    while(llega==-1)pause();

    return llega;

}