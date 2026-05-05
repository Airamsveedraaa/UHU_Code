#include <iostream>
#include <cstdlib>
#include <queue>
#include "arbin.h"
#include "abb.h"
#include "Excep_Ej6.h"

// Recorridos

template <typename T>
void inorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r)
{
    if (!r.arbolVacio())
    {
        inorden(a, a.subIzq(r));
        cout << r.observar() << " ";
        inorden(a, a.subDer(r));
    }
}

template <typename T>
void preorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r)
{
    if (!r.arbolVacio())
    {
        cout << r.observar() << " ";
        preorden(a, a.subIzq(r));
        preorden(a, a.subDer(r));
    }
}

template <typename T>
void postorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r)
{
    if (!r.arbolVacio())
    {
        postorden(a, a.subIzq(r));
        postorden(a, a.subDer(r));
        cout << r.observar() << " ";
    }
}

template <typename T>
void anchura(const Arbin<T>& a)
{
    if (!a.esVacio())
    {
        queue<typename Arbin<T>::Iterador> c;
        typename Arbin<T>::Iterador ic = a.getRaiz();
        c.push(ic);
        while (!c.empty())
        {
            ic = c.front();
            c.pop();
            cout << ic.observar() << " ";
            if (!a.subIzq(ic).arbolVacio())
                c.push(a.subIzq(ic));
            if (!a.subDer(ic).arbolVacio())
                c.push(a.subDer(ic));
        }
    }
}


/***************************************************************************/
/****************************** EJERCICIOS *********************************/
/***************************************************************************/
//Ejercicio 1

template <typename T> int numHojas(const Arbin<T>& a)
{

    return numHojas(a, a.getRaiz());

}

template <typename T> int numHojas(const Arbin<T>& a, const typename Arbin<T>::Iterador& r)
{


    if(r.arbolVacio()) return 0;

    if(a.subDer(r).arbolVacio() && a.subIzq(r).arbolVacio()) return 1;
    else
    {
        return numHojas(a,a.subDer(r)) + numHojas(a,a.subIzq(r));
    }

}

/****************************************************************************/
//Ejercicio 2
template <typename T> Arbin<T> simetrico(const Arbin<T>& a)
{

    return simetrico(a,a.getRaiz());

}

template <typename T> Arbin<T> simetrico(const Arbin<T>&a, const typename Arbin<T>::Iterador& r)
{

    if(r.arbolVacio()) return Arbin<T>();

    else
    {
        return Arbin<T>(r.observar(),simetrico(a,a.subDer(r)),simetrico(a,a.subIzq(r)));
    }

}

/****************************************************************************/
//Ejercicio 3

template <typename T> void recorridoZigzag(const Arbin<T>& a, char sentido)
{

    recorridoZigzag(a,sentido,a.getRaiz());

}


template <typename T> void recorridoZigzag(const Arbin<T>& a, char sentido, const typename Arbin<T>::Iterador& r)
{

    if(!r.arbolVacio())
    {

        cout << r.observar() << " ";
        if (sentido=='I')
        {
            recorridoZigzag(a,'D',a.subIzq(r));
        }
        if(sentido=='D')
        {
            recorridoZigzag(a,'I',a.subDer(r));
        }
    }
}

/******************************************************************************/
//Ejercicio 4


template <typename T> int numNodos(const Arbin<T>& a, const typename Arbin<T>::Iterador& r)
{

    if(r.arbolVacio()) return 0;

    else return numNodos(a,a.subIzq(r)) + numNodos(a,a.subDer(r)) +1 ;

}
template <typename T> bool compensado(const Arbin<T>& a)
{

    return compensado(a,a.getRaiz());

}


template <typename T> bool compensado(const Arbin<T>& a, const typename Arbin<T>::Iterador& r)
{

    if(a.esVacio() || r.arbolVacio())return true;

    if(!compensado(a,a.subIzq(r)) || !compensado(a,a.subDer(r))) return false;
    else return numNodos(a,a.subIzq(r)) - numNodos(a,a.subDer(r)) <=1 && numNodos(a,a.subIzq(r)) - numNodos(a,a.subDer(r)) > -2;

}

/*****************************************************************************/
//Ejercicio 5

template <typename T> void Palabras (const Arbin<T>& a)
{

    Palabras(a, a.getRaiz(),"");
}


template <typename T> void Palabras (const Arbin<T>& a, const typename Arbin<T>::Iterador r, string s)
{

    if(!r.arbolVacio())
    {
        s+=r.observar();
        if(a.subDer(r).arbolVacio() && a.subIzq(r).arbolVacio())
        {
            cout << s << endl;
        }
        else
        {
            Palabras(a,a.subDer(r),s);
            Palabras(a,a.subIzq(r),s);
        }
    }

}

/******************************************************************************/
//Ejercicio 6

int siguienteMayor(const ABB<int>& a, const typename Arbin<int>::Iterador& r,int x)throw (NoHaySiguienteMayor)
{

    if(r.arbolVacio())
    {
        throw NoHaySiguienteMayor();
    }

    if (r.observar() <= x)
    {
        return siguienteMayor(a,a.subDer(r),x);
    }
    else
    {
        try
        {
            return siguienteMayor(a,a.subIzq(r),x);
        }
        catch(const NoHaySiguienteMayor& e)
        {
            return r.observar();

        }
    }
}

int siguienteMayor(const ABB<int>& a,int x)
{

    return siguienteMayor(a,a.getRaiz(),x);

}



/******************************************************************************/
//Ejercicio 7

template <typename T> int posicionInorden(const ABB<T>& a,int x)
{

    return posicionInorden(a,a.getRaiz(),x);

}

template <typename T> int posicionInorden(const ABB<T>& a, const typename ABB<T>::Iterador r,int x )
{

    if(r.arbolVacio())return 0;
    else if(r.observar()==x) return numNodos(a,a.subIzq(r))+1;
    else if (x < r.observar()) return posicionInorden(a,a.subIzq(r),x);
    else
    {
        int pos=posicionInorden(a,a.subDer(r),x);
        if (pos==0)return 0;
        return numNodos(a,a.subIzq(r)) + 1 + pos;
    }
}

/******************************************************************************/
//Ejercicio 8

bool haySumaCamino(const Arbin<int>& a, const typename Arbin<int>::Iterador r, int suma)
{

    if (r.arbolVacio())return false;

        suma=suma-r.observar();
        if(a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio())
            return suma==0;
        return haySumaCamino(a,a.subIzq(r),suma) || haySumaCamino(a,a.subDer(r),suma);

}

bool haySumaCamino(const Arbin<int>& a, int suma)
{

    return haySumaCamino(a,a.getRaiz(),suma);
}


/****************************************************************************/
/****************************************************************************/
int main(int argc, char *argv[])
{
    Arbin<char> A('t', Arbin<char>('m', Arbin<char>(),
                                   Arbin<char>('f', Arbin<char>(), Arbin<char>())),
                  Arbin<char>('k', Arbin<char>('d', Arbin<char>(), Arbin<char>()),
                              Arbin<char>()));

    Arbin<char> B('t', Arbin<char>('n', Arbin<char>(),
                                   Arbin<char>('d', Arbin<char>('e', Arbin<char>(), Arbin<char>()),
                                           Arbin<char>())),
                  Arbin<char>('m', Arbin<char>('f', Arbin<char>(), Arbin<char>()),
                              Arbin<char>('n', Arbin<char>(), Arbin<char>())));

    Arbin<char> D('t', Arbin<char>('k', Arbin<char>('d', Arbin<char>(), Arbin<char>()),
                                   Arbin<char>()),
                  Arbin<char>('m', Arbin<char>(),
                              Arbin<char>('f', Arbin<char>(), Arbin<char>())));

    Arbin<char> E('o', Arbin<char>('r', Arbin<char>(),
                                   Arbin<char>('o', Arbin<char>(), Arbin<char>())),
                  Arbin<char>('l', Arbin<char>('a', Arbin<char>(), Arbin<char>()),
                              Arbin<char>('e', Arbin<char>(), Arbin<char>())));

    Arbin<int> F(2, Arbin<int>(7, Arbin<int>(2, Arbin<int>(), Arbin<int>()),
                               Arbin<int>(6, Arbin<int>(5, Arbin<int>(), Arbin<int>()),
                                          Arbin<int>(11, Arbin<int>(), Arbin<int>()))),
                 Arbin<int>(5, Arbin<int>(),
                            Arbin<int>(9, Arbin<int>(),
                                       Arbin<int>(4, Arbin<int>(), Arbin<int>()))));

    ABB<int> BB6, BB7;



    // NUMERO HOJAS //
    cout << "Num. hojas del arbol B: " << numHojas(B) << endl;
    cout << "Num. hojas del arbol E: " << numHojas(E) << endl << endl;

    // COPIA SIMETRICA //
    Arbin<char> C = simetrico(B);
    cout << "Recorrido en inorden del arbol B: " << endl;
    inorden(B, B.getRaiz());
    cout << endl << "Recorrido en inorden del arbol C: " << endl;
    inorden(C, C.getRaiz());
    cout << endl << endl;


    // RECORRIDO EN ZIG-ZAG //
    cout << "Recorrido en zigzag I de B:\n";
    recorridoZigzag(B, 'I');
    cout << endl;
    cout << "Recorrido en zigzag D de C:\n";
    recorridoZigzag(C, 'D');
    cout << endl << endl;


    // COMPENSADO //
    cout << "Esta A compensado?:";
    cout << (compensado(A) ? " SI" : " NO") << endl;
    cout << "Esta B compensado?:";
    cout << (compensado(B) ? " SI" : " NO") << endl << endl;

    // PALABRAS DE UN ARBOL //
    cout << "PALABRAS DE E:\n";
    Palabras(E);
    cout << "PALABRAS DE B:\n";
    Palabras(B);
    cout << endl;

    // SIGUIENTE MAYOR
    BB6.insertar(8);
    BB6.insertar(3);
    BB6.insertar(10);
    BB6.insertar(1);
    BB6.insertar(6);
    BB6.insertar(14);
    BB6.insertar(4);
    BB6.insertar(7);
    BB6.insertar(13);
    try
    {
        cout << "Siguiente mayor en BB6 de 5: " << siguienteMayor(BB6, 5) << endl;
        cout << "Siguiente mayor en BB6 de 8: " << siguienteMayor(BB6, 8) << endl;
        cout << "Siguiente mayor en BB6 de 13: " << siguienteMayor(BB6, 13) << endl;
        cout << "Siguiente mayor en BB6 de 14: " << siguienteMayor(BB6, 14) << endl;
    }
    catch(const NoHaySiguienteMayor& e)
    {
        cout << e.Mensaje() << endl << endl;
    }

    // POSICION INORDEN //
    BB7.insertar(5);
    BB7.insertar(1);
    BB7.insertar(3);
    BB7.insertar(8);
    BB7.insertar(6);
    cout << "Posicion Inorden en BB7 de 3: ";
    cout << posicionInorden(BB7, 3);
    cout << endl << "Posicion Inorden en BB7 de 8: ";
    cout << posicionInorden(BB7, 8);
    cout << endl << "Posicion Inorden en BB7 de 7: ";
    cout << posicionInorden(BB7, 7);
    cout << endl << endl;

    // SUMA CAMINO
    cout << "Hay un camino de suma 26 en F?:";
    cout << (haySumaCamino(F, 26) ? " SI" : " NO") << endl;
    cout << "Hay un camino de suma 9 en F?:";
    cout << (haySumaCamino(F, 9) ? " SI" : " NO") << endl;


    system("PAUSE");
    return 0;
}
