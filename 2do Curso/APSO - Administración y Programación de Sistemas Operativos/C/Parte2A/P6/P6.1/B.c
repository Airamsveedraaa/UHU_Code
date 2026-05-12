#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>

struct mtipo1
{
    long tipo;
    int num;
};

int main()
{

    srand(getpid());

    printf("Soy el proceso B con pid %d y mi padre es el proceso con pid %d\n", getpid(), getppid());

    struct mtipo1 info;

    key_t clave = ftok("./Makefile", 45); // Crear clave de cola de mensajes

    if (clave == -1)
    {
        perror("A: Error al generar la clave de la cola de mensajes");
        exit(-1);
    }

    int c1 = msgget(clave, 0600 | IPC_CREAT); // abrir/entrar a cola de mensajes

    if (c1 == -1)
    {
        perror("A: Error al abrir/entrar la cola de mensajes");
        exit(-1);
    }

    // Escribir los 10 numeros positivos en intervalos
    for (int i = 0; i < 10; i++)
    {

        info.tipo = 1;
        info.num = rand() % 100 + 1;
        if (msgsnd(c1, &info, sizeof(info) - sizeof(long), 0) == -1)
            perror("B: Error al escribir en la cola de mensajes");
        printf("B: He escrito este dato %d en la cola de mensajes y es del tipo %ld\n", info.num, info.tipo);
        sleep(rand() % 3 + 1);
    }

    printf("Fin del proceso B\n");

    return 0;
}