#include "ContratoTP.h"

float ContratoTP::precioTP=10;
int ContratoTP::minutosTP=300;
const float ContratoTP::precioExcesoMinutos=0.15;

ContratoTP::ContratoTP( long int dni,const Fecha& f, int m):Contrato(dni,f)
{
    this->minutosHablados=m;
}

ContratoTP::ContratoTP(const ContratoTP& c):Contrato(c)
{
    this->minutosHablados=c.minutosHablados;
}

float ContratoTP::factura()const
{
    float factura;;
    if(minutosHablados > minutosTP)
        factura=precioTP+(precioExcesoMinutos*(minutosHablados-minutosTP));
    else
        factura=precioTP;
    return factura;
}

void ContratoTP::ver()const
{
    Contrato::ver();
    cout << " " << this->minutosHablados << "m, ";
    cout << this->minutosTP << "(" << fixed << setprecision(2)
         << this->precioTP << ") - " << this->factura() << "E";
}


ostream& operator<<(ostream& s,const ContratoTP& c)
{
    s << c.getDniContrato() << " (" << c.getIdContrato() << " - " << c.getFechaContrato() << " )"<<c.getMinutosHablados()<<"m, "<<c.getLimiteMinutos()<<"("<<c.getPrecio()<<") - "<<c.factura()<<"E"<<endl;
    return s;
}

ContratoTP::~ContratoTP()
{
}
