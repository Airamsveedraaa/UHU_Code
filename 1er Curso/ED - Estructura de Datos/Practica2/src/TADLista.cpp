#include "TADLista.h"


lista::lista()
{
    elementos=NULL;
    n=0;
}


lista::lista(Jugador e)
{
 elementos=new TNodo_Lista;
 elementos->Datos=e;
 elementos->Siguiente=NULL;
 n=1;
}


lista::~lista()
{
    TNodo_Lista *Nodo_Borr=elementos,*Nodo_Sig;
    while (Nodo_Borr!=NULL)
    {
        Nodo_Sig=Nodo_Borr->Siguiente;
        delete Nodo_Borr;
        Nodo_Borr=Nodo_Sig;
    }
    elementos=NULL;
    n=0;
}


TNodo_Lista *lista::Anterior(int i)
{
    TNodo_Lista *Nodo_Aux=elementos,*Nodo_Ant=NULL;
    int v=1;
    if (Nodo_Aux!=NULL)
        while (Nodo_Aux!=NULL && v<i)
        {
            Nodo_Ant=Nodo_Aux;
            Nodo_Aux=Nodo_Aux->Siguiente;
            v++;
        }
    return Nodo_Ant;
};


void lista::insertar(int i, Jugador e)
{
    TNodo_Lista *Nodo_Aux=new TNodo_Lista, *Nodo_Ant;
    if (Nodo_Aux!=NULL)
    {
        Nodo_Aux->Datos=e;
        Nodo_Aux->Siguiente=NULL;
        Nodo_Ant= Anterior(i);
        if (Nodo_Ant==NULL)
        {
            Nodo_Aux->Siguiente=elementos;
            elementos=Nodo_Aux;
        }
        else
        {
            Nodo_Aux->Siguiente=Nodo_Ant->Siguiente;
            Nodo_Ant->Siguiente=Nodo_Aux;
        }
        n++;
    }
}


void lista::eliminar(int i)
{
    TNodo_Lista *Nodo_Ant,*Nodo_Aux;
    Nodo_Ant=Anterior(i);
    if (Nodo_Ant==NULL)
    {
        Nodo_Aux=elementos;
        elementos=Nodo_Aux->Siguiente;
    }
    else
    {
        Nodo_Aux=Nodo_Ant->Siguiente;
        Nodo_Ant->Siguiente=Nodo_Aux->Siguiente;
    }
    delete Nodo_Aux;
    n--;
}


void lista::modificar(int i, Jugador e)
{
    TNodo_Lista *Nodo_Ant=Anterior(i),*Nodo_Aux;
    if (Nodo_Ant==NULL)
        Nodo_Aux=elementos;
    else
        Nodo_Aux=Nodo_Ant->Siguiente;
    Nodo_Aux->Datos=e;
}


Jugador lista::observar(int i)
{
    TNodo_Lista *Nodo_Ant=Anterior(i),*Nodo_Aux;
    if (Nodo_Ant==NULL)
        Nodo_Aux=elementos;
    else
        Nodo_Aux=Nodo_Ant->Siguiente;
    return Nodo_Aux->Datos;
}


bool lista::esvacia ()
{
 return (n == 0);
}


int lista::longitud ()
{
 return n;
}


int lista::posicion(Jugador e)
{
 TNodo_Lista *Nodo_Aux=elementos;
 bool encontrado=false;
 int v=1;
 while (Nodo_Aux!=NULL && !encontrado)
 if (strcmp(Nodo_Aux->Datos.nombreJugador,e.nombreJugador)!=0)
 {
 Nodo_Aux=Nodo_Aux->Siguiente;
 v++;
 }
 else
 encontrado=true;

 return (encontrado?v:-1);
}

void lista::anadirDch(Jugador e){

insertar(n+1,e);

}

void lista::anadirIzq(Jugador e){

insertar(1,e);

}


void lista::eliminarDch(){

eliminar(n);

}

void lista::eliminarIzq(){

eliminar(1);

}

Jugador lista::observarIzq(){

return observar(1);

}

Jugador lista::observarDch(){

return observar(n);

}

