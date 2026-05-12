#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{

    printf("Soy el proceso A con pid %d\n", getpid());

    int pidb = fork();

    if (pidb == 0)
    {

        close(1); // cerrar salida estandar para que b redireccione
        int f1 = open("infoB", O_CREAT | O_WRONLY, 0600);
        if (f1 == -1)
            perror("Error en el open");
        execl("B", "B", NULL);
        perror("Error en execl de B");
        exit(-1);
    }
    else if (pidb == -1)
        perror("Error en el fork de B");

    printf("A: Proceso B creado con pid %d, mi pid es %d\n", pidb, getpid());
    wait(NULL);
    sleep(2);

    printf("Fin del proceso A");

    return 0;
}