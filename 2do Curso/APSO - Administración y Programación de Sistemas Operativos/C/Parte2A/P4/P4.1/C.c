#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int llegaAlarm,llega10=0;

void alrm(int signal){
    printf("C: ALARMA!\n");
    llegaAlarm=1;
}

void usr1(int signal){
    llega10=1;
}

int main(){

    signal(14,alrm);
    signal(10,usr1);
    if(!llega10)pause();
    llega10=0;
    printf("C: Tercer Mensaje\n");

    alarm(3);

    while(!llegaAlarm){
        printf("C: Esperando Alarma...\n");
        sleep(1);
    }
    printf("C: Cuarto Mensaje\n");

    if(kill(getppid(),12)==-1)perror("C: Error en el kill");

    return 0;
}