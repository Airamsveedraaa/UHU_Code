#ifndef TADLISTA_H_INCLUDED
#define TADLISTA_H_INCLUDED
#include "Comun.h"

struct TNodo_Lista
{
    Jugador Datos; // Dato a almacenar en cada nodo
    TNodo_Lista *Siguiente; // Puntero al siguiente nodo
};
class lista
{
    TNodo_Lista *elementos; // Puntero al primer nodo de la lista.
    int n; // nº de nodos que tiene la lista
// Devuelve un puntero al elemento anterior al elemento i
// Devuelve NULL si es el primero
    TNodo_Lista *Anterior(int i);
public:
    lista(); // constructor de la clase
    ~lista(); // destructor de la clase
    lista(Jugador e);
    bool esvacia();
    int longitud();
    void anadirIzq(Jugador e);
    void anadirDch(Jugador e);
    void eliminarIzq();
    void eliminarDch();
    Jugador observarIzq();
    Jugador observarDch();
    void concatenar(lista l);
    bool pertenece(Jugador e);
    void insertar(int i, Jugador e);
    void eliminar(int i);
    void modificar(int i, Jugador e);
    Jugador observar(int i);
    int posicion(Jugador e);
};
#endif // TADLISTA_H_INCLUDED
