#include "Persona.h"

Persona::Persona(const string& n, int e){

this->nombre=n;
this->edad=e;

}

const string& Persona::getNombre()const{

return this->nombre;

}

int Persona::getEdad()const{

return this->edad;

}


void Persona::setNombre(const string& n){

this->nombre=n;

}


void Persona::setEdad(int e){

this->edad=e;

}


bool Persona::operator==(const Persona& p)const{

return this->edad==p.getEdad() && this->nombre==p.getNombre();

}


ostream& operator<<(ostream& s, const Persona& P){

s << "nombre: " << P.getNombre() << "edad: " << P.getEdad();

return s;
}
