#ifndef TADCOLA_H_INCLUDED
#define TADCOLA_H_INCLUDED
#include "Comun.h"

struct TNodo_Cola
{
    Jugador Datos; //Datos a almacenar en cada nodo
    TNodo_Cola *Siguiente; //Puntero al siguiente nodo
};
class cola
{
    TNodo_Cola *Inicio; //Puntero al inicio de la cola.
    TNodo_Cola *Fin; //Puntero al fin de la cola.
    int ne; //nº de nodos que tiene la lista
public:
    cola(); //constructor de la clase
    ~cola(); //destructor de la clase
    void encolar(Jugador e);
    void desencolar();
    bool esvacia();
    Jugador primero() ;
    int longitud();
};
#endif // TADCOLA_H_INCLUDED
