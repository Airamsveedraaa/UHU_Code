#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>



int llega12=0;
void R12(int signal){
    llega12=1;
}



int main(){

    srand(getpid());
    signal(12,R12);

    if(!llega12)
    pause();
    llega12=0;

    int n=rand() %3 +2;

    printf("C: Me duermo %d segundos y aviso a mi padre\n",n);
    sleep(n);

    if(kill(getppid(),12)==-1)perror("C: Error en kill a B");

    return 0;
}