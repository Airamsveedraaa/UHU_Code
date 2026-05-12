#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>

struct mtipo2
{
    long tipo;
    int num;
};

int main()
{

    struct mtipo2 info;
    srand(getpid());

    printf("Soy el proceso C con pid %d y mi padre es el proceso con pid %d\n", getpid(), getppid());

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

    // Escribir los 10 numeros aleatorios NEGATIVOS

    for (int i = 0; i < 10; i++)
    {
        info.tipo = 2;
        info.num = -(rand() % 100 + 1);
        if (msgsnd(c1, &info, sizeof(info) - sizeof(long), 0) == -1)
            perror("C: Error al escribir en la cola de mensajes");
        printf("C: He escrito esto %d en la cola de mensajes y es del tipo %ld\n", info.num, info.tipo);
        sleep(rand() % 3 + 1);
    }

    printf("Fin del proceso C\n");

    return 0;
}