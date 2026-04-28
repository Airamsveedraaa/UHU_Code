#include <cstdlib>
#include <iostream>
# include "cartelera.h"  

using namespace std;  
 
int main(int argc, char *argv[])
{
    Cartelera c;
    
     c.insertaEspectaculo("The Creator");
     c.insertaEspectaculo("Oppenheimer"); 
     c.insertaEspectaculo("Blue Beetle");
     c.insertaEspectaculo("Dune: Parte Dos");
     c.insertaEspectaculo("Napoleón");
     c.insertaEspectaculo("La sociedad de la nieve");
     c.insertaEspectaculo("Wonka");
     c.listaEspectaculos();
    cout << endl;
    c.insertaSala("Wonka", "Al Andalus", "Punta Umbria");
    c.insertaSala("Wonka", "Cinebox Aqualon Puerto", "Huelva");
    c.insertaSala("Wonka", "La Dehesa", "Isla Antilla");
    c.insertaSala("Wonka", "Artesiete Holea", "Huelva");
    c.insertaEspectaculo("Wonka");
    
    c.listaSalas("Wonka"); 
    cout << endl;
    
    c.eliminaSala("Wonka", "La Dehesa");
    cout << "Despues de eliminar la sala La Dehesa del espectaculo **Wonka**" << endl;
    c.listaSalas("Wonka");
    cout << endl;

    c.eliminaEspectaculo("Wonka");
    cout << "Despues de eliminar el espectaculo **Wonka**" << endl;
    c.listaEspectaculos();
    cout << endl;

    cout << "**Wonka** ya se elimino como espectaculo." << endl;
    cout << "Despues de eliminar la sala La Dehesa de un espectaculo que no existe" << endl;

    c.eliminaSala("Wonka", "La Dehesa");
    c.listaEspectaculos();
    cout << endl;

    c.listaSalas("Wonka");
    c.listaEspectaculos();

    system("PAUSE");
    return EXIT_SUCCESS;
}

