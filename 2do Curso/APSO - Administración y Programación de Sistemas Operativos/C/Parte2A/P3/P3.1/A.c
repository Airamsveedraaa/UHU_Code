#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{

    printf("Soy el proceso A, con pid: %d \n", getpid());

    int vpidb = fork();

    if (vpidb == 0)
    {

        execl("B", "B", NULL); // devuelve error solo, no se maneja explicitamente
        perror("Error en execl de B");
        exit(-1);
    }
    else if (vpidb == -1)
        perror("Error en el fork de B"); // manejo de error del fork

    int vpidc = fork();

    if (vpidc == 0)
    {

        close(1);
        int infoc = open("infoc", O_CREAT | O_WRONLY, 0600); // redireccionamos la salida de C al fichero
        if (infoc == -1)
            perror("Error en la apertura del fichero"); // manejo de error de la apertura de fichero

        execl("C", "C", NULL); // devuelve error solo, no se maneja explicitamente
        perror("Error en execl de C");
        exit(-1);
    }
    else if (vpidc == -1)
        perror("Error en el fork de C"); // manejo de error del fork

    printf("A: Proceso C lanzado con pid %d\n", vpidc);
    printf("A: Proceso B lanzado con pid %d\n", vpidb);

    wait(NULL);
    wait(NULL); // Esperar a que acaben B y C para finalizar proceso padre
    sleep(4);
    printf("Fin del proceso A\n");

    return 0;
}