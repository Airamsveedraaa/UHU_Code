#include "ContratoMovil.h"

ContratoMovil::ContratoMovil( long int dni,const Fecha& f, float p, int m, char* nac):Contrato(dni,f)
{
    this->precio=p;
    this->minutosHablados=m;
    this->nacionalidad=new char[strlen(nac)+1];
    strcpy(this->nacionalidad,nac);
}

ContratoMovil::ContratoMovil(const ContratoMovil& c):Contrato(c)
{
    this->nacionalidad=new char[strlen(c.nacionalidad)+1];
    strcpy(this->nacionalidad,c.nacionalidad);
    this->precio=c.precio;
    this->minutosHablados=c.minutosHablados;
}

float ContratoMovil::factura()const
{
    return this->precio*this->minutosHablados;
}

void ContratoMovil::ver()const
{
    Contrato::ver();
    cout << " " << this->minutosHablados << "m, ";
    cout << this->getNacionalidad();
    cout << " " << fixed << setprecision(2) << this->precio
         << " - " << this->factura() << "E";
}


void ContratoMovil::setNacionalidad(const char* nac)
{
    delete [] this->nacionalidad;
    this->nacionalidad=new char[(strlen(nac)+1)];
    strcpy(this->nacionalidad,nac);
}

ostream& operator<<(ostream& s,const ContratoMovil& c)
{
    s << c.getDniContrato() << " (" << c.getIdContrato() << " - " << c.getFechaContrato() << " )"<<c.getMinutosHablados()<<"m, "<<c.getNacionalidad()<<" "<<c.getPrecioMinuto()<<" - "<<c.factura()<<"E"<<endl;
    return s;
}

ContratoMovil::~ContratoMovil()
{
    delete [] this->nacionalidad;
}
