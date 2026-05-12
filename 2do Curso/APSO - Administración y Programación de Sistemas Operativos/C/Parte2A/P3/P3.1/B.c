#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{

    printf("Soy el proceso B con pid %d y mi padre es el proceso con pid %d\n", getpid(), getppid());

    int copia = fork();

    if (copia == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Soy el proceso B copia, mi pid es %d, y el de mi padre es %d\n", getpid(), getppid());
            sleep(1); // tiempo de espera entre iteraciones
        }
        exit(0);
    }
    if (copia == -1)
        perror("Error en fork de B copia"); // manejo de error del fork

    for (int i = 0; i < 3; i++)
    {
        printf("Soy el proceso B, mi pid es %d, y el de mi padre es %d\n", getpid(), getppid());
        sleep(1);
    }

    printf("Fin del proceso B\n");

    return 0;
}