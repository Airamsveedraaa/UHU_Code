#include "cartelera.h"
#include <iostream>

using namespace std;

Cartelera::Cartelera(): espectaculos()
{

}

void Cartelera::insertaEspectaculo(const string& e)
{

    espectaculos.insert(PEspectaculos(e,DSalas()));

}

void Cartelera::insertaSala(const string& e, const string& s, const string& c)
{

    espectaculos[e].insert(PSalas(s,c));

}

void Cartelera::eliminaEspectaculo(const string& e)
{

    espectaculos.erase(e);
}

void Cartelera::eliminaSala(const string& e, const string& s)
{
    DEspectaculos::iterator it=espectaculos.find(e);
    if(it != espectaculos.end())
        it->second.erase(s);

}

void Cartelera::listaEspectaculos()
{
    if(espectaculos.empty())
        cout << "No hay espectaculos" << endl;
    else
    {
        cout << "Lista de espectaculos: " << endl;
        DEspectaculos::iterator it;
        for(it=espectaculos.begin(); it != espectaculos.end(); it++)
        {
            cout << it->first << endl;
        }
    }

}

void Cartelera::listaSalas(const string& e)
{

    DEspectaculos::iterator it = espectaculos.find(e);
    if(it==espectaculos.end())
        cout << "No existe ningun espectaculo" << endl;
    else
    {
        if(it->second.empty())
            cout << "No hay ninguna sala para el espectaculo " << e << endl;
        else
        {
            DSalas::iterator is;
            for(is=it->second.begin(); is != it->second.end(); is++)
            {
                cout << is->first << " - " << is->second << endl;
            }
        }
    }

}

