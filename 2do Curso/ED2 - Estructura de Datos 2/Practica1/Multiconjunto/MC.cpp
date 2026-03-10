#include "MC.h"

template <typename T> Multiconjunto<T>::Multiconjunto()
{

    this->num=0; //inicializado de primeras a 0 elementos efectivos

}

template <typename T> bool Multiconjunto<T>::esVacio()const
{

    return this->num==0; //si es 0 está vacío, sino no

}

template <typename T> int Multiconjunto<T>::cardinalidad()const
{

    return this->num; //número de elementos efectivos

}

template <typename T> void Multiconjunto<T>::anade(const T& objeto)
{

    this->c[this->num]=objeto;
    this->num++; //como se permiten repetidos, y no pide logica concreta, simplemente añadimos e incrementamos

}

template <typename T> void Multiconjunto<T>::elimina(const T& objeto)
{

    int i=0;

    while(i<this->num)
    {
        if(this->c[i]==objeto)
        {
            for(int j=i; j<this->num-1; j++)
            {
                this->c[j]=this->c[j+1];
            }
            this->num--;
        }
        else
        {
            i++;
        }
    }

}


template <typename T> bool Multiconjunto<T>::pertenece(const T& objeto)const
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
