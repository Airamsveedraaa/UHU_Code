#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int llega10 = 0;

void R10(int signal)
{

    llega10 = 1;
}

int main()
{

    signal(10, R10);
    srand(getpid());

    printf("Soy el proceso A con pid %d\n", getpid());

    int pidb = fork();

    if (pidb == 0)
    {

        execl("B", "B", NULL);
        perror("Error en execl de B");
        exit(-1);
    }
    else if (pidb == -1)
        perror("A: Error en el fork de B");

    if (!llega10)
        pause();
    llega10 = 0;

    int n = rand() % 3 + 2;
    sleep(n);

    if (kill(pidb, 10) == -1)
        perror("A: Error en kill a B");

    int res;
    wait(&res);
    if (WIFEXITED(res))
    {
        int valor=WEXITSTATUS(res);
        if(valor==0)
        printf("A: Juego abortado\n");
        else if (valor == 1) 
        printf("A: Gano Yo\n");
        else if (valor == 2) 
        printf("A: Gana C\n");
    }

    return 0;
}