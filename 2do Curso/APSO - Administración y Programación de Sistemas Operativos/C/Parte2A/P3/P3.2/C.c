#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv []){

    printf("Soy el proceso C, con pid %d, el pid de mi padre es %d y el argumento que he recibido es %s\n", getpid(),getppid(),argv[1]);


    printf("Fin del proceso C\n");
    return 0;
}