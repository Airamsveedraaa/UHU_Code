#include "MC.h"

template <typename T> Multiconjunto::Multiconjunto()
{

    this->num=0; //inicializado de primeras a 0 elementos efectivos

}

template <typename T> bool Multiconjunto::esVacio()const
{

    return this->num==0; //si es 0 está vacío, sino no

}

template <typename T> int Multiconjunto::cardinalidad()const
{

    return this->num; //número de elementos efectivos

}

template <typename T> void Multiconjunto::anade(const T& objeto)
{

    this->c[this->num]=objeto;
    this->num++; //como se permiten repetidos, y no pide logica concreta, simplemente añadimos e incrementamos

}

template <typename T> void Multiconjunto::elimina(const T& objeto)
{

    for(int i=0; i<this->num; i++)
    {
        if(this->c[i]==objeto)
        {
            T temp=this->c[i+1];
            this->c[i]=temp;
            this->num--;
        }
    }

}


template <typename T> bool Multiconjunto::pertenece(const T& objeto)const
{

    bool encontrado=false;

    int i=0;
    while(!encontrado && i<this->num)
    {

        if(this->c[i]==objeto)
        {
            encontrado=true;
        }
        i++;
    }

    return encontrado;
}

template class Multiconjunto<int>;
template class Multiconjunto<char>;
