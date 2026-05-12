#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{

    printf("Proceso A creado con pid %d\n", getpid());

    int tubo[2];

    pipe(tubo);

    mkfifo("FIFOAC", 0600);

    int pidb = fork();

    if (pidb == 0)
    {
        close(2);
        dup(tubo[1]);
        execl("B", "B", NULL);
        perror("A: Error en execl de B");
        exit(-1);
    }
    else if (pidb == -1)
        perror("A: Error en fork de B");

    close(tubo[1]);

    int fifo = open("FIFOAC", O_RDONLY);
    if (fifo == -1)
        perror("A: Error al abrir la FIFO");

    int datosB[10], datosC[10];
    int i = 0;
    int datoB, datoC;
    float mediaB = 0, mediaC = 0;

    int pidC;
    if (read(tubo[0], &pidC, sizeof(int)) == -1)
        perror("A: Error al leer de la PIPE");
    if (pidC == -1)
        perror("A: Error al leer de la PIPE");

    for(int i=0; i<5;i++)
    {   
        if(read(tubo[0],&datoB,sizeof(int))==-1){
            perror("A: Error al leer de la PIPE"); 
            exit(-1);
        }
        printf("A: He recibido este numero a traves de la PIPE %d y lo envia el proceso con pid %d\n", datoB, pidb);
        datosB[i] = datoB;

        if(read(fifo, &datoC, sizeof(int))==-1){
            perror("A: Error al leer de la FIFO");
            exit(-1);
        }

        printf("A: He recibido este numero a traves de la FIFO %d y lo envia el proceso con pid %d\n", datoC, pidC);
        datosC[i] = datoC;
    }

    for (int i = 0; i < 5; i++)
    {
        mediaB += datosB[i];
        mediaC+= datosC[i];
    }
    mediaB = mediaB / 5;
    mediaC = mediaC / 5;


    if(mediaB > mediaC){
        if(kill(pidb,10)==-1)perror("A: Error en kill a B");
    }
    else{
        if(kill(pidb,12)==-1)perror("A: Error en kill a B");
    }

    wait(NULL);

    close(fifo);
    unlink("FIFOAC");

    printf("Fin del proceso A\n");
    return 0;
}