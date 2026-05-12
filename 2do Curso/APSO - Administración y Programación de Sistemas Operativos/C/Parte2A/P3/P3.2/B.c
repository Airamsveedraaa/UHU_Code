#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{

    srand(getpid()); // semilla aleatoria
    printf("Soy el proceso B \n");
    int n = rand() % 10 + 1;
    char cad[1];
    sprintf(cad, "%d", n);

    int pidc = fork();

    if (pidc == 0)
    {

        close(1);
        int f2 = open("/dev/tty", O_WRONLY, 0600);
        if (f2 == -1)
            perror("Error al abrir el fichero dev/tty");

        execl("C", "C", cad, NULL);
        perror("Error en execl de C");
        exit(-1);
    }
    else if (pidc == -1)
        perror("Error en el fork de C");

    printf("B: He creado el proceso C con pid %d, mi pid es %d, y el de mi padre es %d\n", pidc, getpid(), getppid());
    wait(NULL);
    sleep(1);
    printf("Fin del proceso B\n");

    return 0;
}