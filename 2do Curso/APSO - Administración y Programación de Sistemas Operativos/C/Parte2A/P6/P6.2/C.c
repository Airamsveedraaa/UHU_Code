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

    key_t clave = ftok("./Makefile", 46); // creacion clave de la cola 2

    if (clave == -1)
    {
        perror("C: Error al generar la clave de la cola de mensajes 2");
        exit(-1);
    }

    int c2 = msgget(clave, 0600 | IPC_CREAT); // entrar/abrir cola de mensajes 2

    if (c2 == -1)
    {
        perror("C: Error al entrar/abrir la cola de mensajes 2");
        exit(-1);
    }

    // Enviar los  5 numeros

    printf("Soy el proceso C con pid %d y mi padre es el proceso con pid %d\n", getpid(), getppid());

    for (int i = 0; i < 5; i++)
    {
        info.tipo = i + 1;
        info.num = i + 1;
        if (msgsnd(c2, &info, sizeof(info) - sizeof(long), 0) == -1)
            perror("C: Error al escribir en la cola de mensajes 2");
        printf("C: He escrito esto %d en la cola de mensajes 2 y es del tipo %ld\n", info.num, info.tipo);
        sleep(rand() % 3 + 1);
    }


    printf("Fin del proceso C\n");

    return 0;
}