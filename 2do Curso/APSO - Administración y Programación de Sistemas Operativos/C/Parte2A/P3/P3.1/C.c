#include <stdio.h>
#include <unistd.h>

int main()
{

    printf("Soy el proceso C con pid %d, y el pid de mi padre es %d\n", getpid(), getppid());

    printf("Fin del proceso C\n");
    return 0;
}