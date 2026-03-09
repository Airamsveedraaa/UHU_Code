#include "Contrato.h"

int Contrato::contador=1;

Contrato::Contrato( long int dni,const Fecha& fechaContrato):fechaContrato(fechaContrato),idContrato(contador)
{
    contador++;
    this->dniContrato=dni;
    //ctor
}

Contrato::Contrato(const Contrato& c):fechaContrato(c.fechaContrato),idContrato(c.idContrato){

this->dniContrato=c.dniContrato;

}

void Contrato::ver()const{

cout << this->dniContrato << " (" << this->idContrato << " - " << this->fechaContrato << ")";

}


ostream& operator<<(ostream& s,const Contrato& c){

s << c.getDniContrato() << " (" << c.getIdContrato() << " - " << c.getFechaContrato() << " )";
return s;

}


Contrato::~Contrato()
{
    //dtor
}
