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

int main()
{
    srand(getpid());
    struct mtipo1 info;

    key_t clave = ftok("./Makefile", 45); // Creacion clave para cola 1

    if (clave == -1)
    {
        perror("A: Error al crear la clave para la cola de mensajes");
        exit(-1);
    }

    int c1 = msgget(clave, 0600 | IPC_CREAT); // entrar/abrir la cola de mensajes

    if (c1 == -1)
    {
        perror("A: Error al entrar/abrir la cola de mensajes");
        exit(-1);
    }

    printf("Soy el proceso A con pid %d\n", getpid());

    int pidb = fork();

    if (pidb == 0)
    {

        execl("B", "B", NULL);
        perror("A: Error de execl de B");
        exit(-1);
    }
    else if (pidb == -1)
        perror("A: Error de fork de B");

    // Enviar numeros
    for (int i = 0; i < 5; i++)
    {
        info.tipo = i+1;
        info.num = i + 1;
        if (msgsnd(c1, &info, sizeof(info) - sizeof(long), 0) == -1)
            perror("A: Error al escribir en la cola de mensajes");
        printf("A: He escrito esto %d en la cola de mensajes y es del tipo %ld\n", info.num, info.tipo);
        sleep(rand() % 3 + 1);
    }

    wait(NULL);

    printf("Fin del proceso A\n");

    msgctl(c1,IPC_RMID,NULL);

    return 0;
}