#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/msg.h>

struct mtipo1
{
    long tipo;
    int num;
};

struct mtipo2{
    long tipo;
    int num;
};

int main()
{

    struct mtipo1 info1;
    struct mtipo2 info2;

    key_t clave1 = ftok("./Makefile", 45); // Crear clave de la cola 1

    if (clave1 == -1)
    {
        perror("B: Error al crear la clave de la cola de mensajes 1");
        exit(-1);
    }

    int c1 = msgget(clave1, 0600 | IPC_CREAT); // Entrar abrir la cola 1

    if (c1 == -1)
    {
        perror("B: Error al entrar/abrir la cola de mensajes 1");
        exit(-1);
    }

        key_t clave2 = ftok("./Makefile", 46); // Crear clave de la cola 2

    if (clave2 == -1)
    {
        perror("B: Error al crear la clave de la cola de mensajes 2");
        exit(-1);
    }

    int c2 = msgget(clave2, 0600 | IPC_CREAT); // Entrar abrir la cola 2

    if (c2 == -1)
    {
        perror("B: Error al entrar/abrir la cola de mensajes 1");
        exit(-1);
    }

    printf("Soy el proceso B con pid %d y mi padre es el proceso con pid %d\n", getpid(), getppid());

    int pidc = fork();

    if (pidc == 0)
    {

        execl("C", "C", NULL);
        perror("B: Error de execl de C");
        exit(-1);
    }
    else if (pidc == -1)
        perror("B: Error de fork de C");

    for (int i = 0; i < 5; i++)
    {
        if (msgrcv(c1, &info1, sizeof(info1) - sizeof(long), i+1, IPC_NOWAIT) == -1)
            printf("B: A NO pone a tiempo el dato %d\n", i+1);
        else
            printf("B: A pone a tiempo el dato %d del tipo %ld en la cola de mensajes 1\n", info1.num, info1.tipo);

        if(msgrcv(c2,&info2,sizeof(info2) - sizeof(long),i+1,IPC_NOWAIT)==-1)
            printf("B: C NO pone a tiempo el dato %d\n",i+1);
        else
            printf("B: C pone a tiempo el dato %d del tipo %ld en la cola de mensajes 2\n",info2.num,info2.tipo);
        sleep(2);
    }

    wait(NULL);

    printf("Fin del proceso B\n");

    msgctl(c2,IPC_RMID,NULL);

    return 0;
}