#include "cartelera.h"
#include <iostream>

using namespace std;

Cartelera::Cartelera(): espectaculos()
{

}

void Cartelera::insertaEspectaculo(const string& e)
{

    if(espectaculos.find(e) == espectaculos.end())
        espectaculos[e]=DSalas();

}

void Cartelera::insertaSala(const string& e, const string& s, const string& c)
{

    if(espectaculos[e].find(s) == espectaculos[e].end())
    {
        espectaculos[e][s]=c;
    }

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

    DEspectaculos::iterator it;
    for(it=espectaculos.begin(); it != espectaculos.end(); it++)
    {
        cout << it->first << endl;
    }

}

void Cartelera::listaSalas(const string& e)
{

    DEspectaculos::iterator it = espectaculos.find(e);
    if(it==espectaculos.end()) return;
    DSalas::iterator is;
    for(is=it->second.begin(); is != it->second.end(); is++)
    {
        cout << is->first << " - " << is->second << endl;
    }

}

