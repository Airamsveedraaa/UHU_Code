#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int llega12=0;

void usr2(int signal){
    llega12=1;
}

int main(){

    signal(12,usr2);

    if(!llega12)pause();
    llega12=0;
    printf("B: Segundo mensaje\n");
    if(kill(getppid(),10)==-1)perror("B: Error en kill a A");
    if(!llega12){
        pause();
    }
    llega12=0;
    printf("B: Quinto Mensaje\n");
    return 0;
}