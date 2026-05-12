#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>


struct mtipo1{
    long tipo;
    int num;
};

struct mtipo2{
    long tipo;
    int num;
};


int main(){

    printf("Soy el proceso A con pid %d\n",getpid());

    struct mtipo1 info1;
    struct mtipo2 info2;

    key_t clave=ftok("./Makefile",45); //Crear clave de cola de mensajes

    if(clave==-1){
        perror("A: Error al generar la clave de la cola de mensajes");
        exit(-1);
    }

    int c1=msgget(clave, 0600 | IPC_CREAT); //abrir/entrar a cola de mensajes

    if(c1==-1){
        perror("A: Error al abrir/entrar la cola de mensajes");
        exit(-1);
    }

    int pidb,pidc;

    pidb=fork();

    if(pidb==0){

        execl("B","B",NULL);
        perror("A: Error en execl de B");
        exit(-1);
    }else if(pidb==-1)perror("A: Error en fork de B");


    pidc=fork();

    if(pidc==0){

        execl("C","C",NULL);
        perror("A: Error en execl de C");
        exit(-1);
    }else if(pidc==-1)perror("A: Error en fork de C");

    for(int i=0;i<10;i++){

        if(msgrcv(c1,&info1,sizeof(info1) - sizeof(long),1,0)==-1)perror("A: Error al recibir el mensaje de la cola de mensajes");
        printf("A: He extraido esto de la cola de mensajes %d y es del tipo %ld\n",info1.num,info1.tipo);

        if(msgrcv(c1,&info2,sizeof(info2) - sizeof(long),2,0)==-1)perror("A: Error al recibir el mensaje de la cola de mensajes");
        printf("A: He extraido esto de la cola de mensajes %d y es del tipo %ld\n",info2.num,info2.tipo);
    }

    wait(NULL);
    wait(NULL);

    printf("Fin del proceso A\n");

    msgctl(c1,IPC_RMID,NULL);

    return 0;
}