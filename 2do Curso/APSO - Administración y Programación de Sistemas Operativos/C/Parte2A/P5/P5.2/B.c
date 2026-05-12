#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int llega10=0,llega12=0;

void R10(int signal){
    llega10=1;
}

void R12(int signal){
    llega12=1;
}


int main()
{

    srand(getpid());
    signal(10,R10);
    signal(12,R12);

    printf("Soy el proceso B con pid %d y mi padre es el proceso con pid %d\n", getpid(), getppid());

    int pidc = fork();

    if (pidc == 0)
    {

        execl("C", "C", NULL);
        perror("B: Error en execl de C");
        exit(-1);
    }
    else if (pidc == -1)
        perror("B: Error en fork de C");

    int escribePipe = dup(2);
    close(2);

    int p = open("/dev/tty", O_WRONLY, 0600);

    if (p == -1)
        perror("B: Error al restablecer la salida de errores");

    if (write(escribePipe, &pidc, sizeof(int)) == -1)
        perror("B: Error al escribir en la PIPE");

    for (int i = 0; i < 5; i++)
    {
        int dato = rand() % 4 + 1;

        int pipe = write(escribePipe, &dato, sizeof(int));
        if (pipe == -1)
            perror("B: Error al escribir en la PIPE");
    }

    close(escribePipe);

    if(!llega10 && !llega12)pause();
    
    if(llega10){
        printf("B: Gano Yo\n");
        if(kill(pidc,12)==-1)perror("B: Error en kill a C");
        llega10=0;
    }

     if(llega12){
        printf("B: Pierdo Yo\n");
        if(kill(pidc,10)==-1)perror("B: Error en kill a C");
        llega12=0;
    }

    printf("Fin del proceso B\n");

    wait(NULL);

    return 0;
}