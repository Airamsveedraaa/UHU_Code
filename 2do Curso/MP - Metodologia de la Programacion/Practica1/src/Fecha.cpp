#include "Fecha.h"


Fecha::Fecha( int dia, int mes, int anio)
{
    this->setFecha(dia,mes,anio);
    //ctor
}


void Fecha::setFecha( int dia, int mes, int anio)
{

    int dmax,diaMes[]= {0,31,28,31,30,31,30,31,31,30,31,30,31};
    this->anio=anio;
    if(this->bisiesto())
        diaMes[2]=29;
    if(mes<1)
        this->mes=1;
    else if(mes>12)
        this->mes=12;
    else
        this->mes=mes;
    dmax=diaMes[this->mes];

    if(dia>dmax)
        this->dia=dmax;
    else if(dia<1)
        this->dia=1;
    else
        this->dia=dia;
}

void Fecha::ver()const
{
    if(this->dia <10 )
        cout << "0";
    cout << this->dia << "/";
    if(this->mes <10)
        cout << "0";
    cout << this->mes << "/" << this->anio;


}


bool Fecha::bisiesto()const
{

    if(this->anio%400==0 || this->anio%4==0 && this->anio%100!=0)
        return true;
    else
        return false;

}

Fecha Fecha::operator++(int i)
{

    Fecha copia = *this; //guardo una copia de la fecha.
    //Incremento la fecha original.
    int dmax, diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (this->bisiesto()) //si el año es bisiesto febrero tiene 29 dias
      diaMes[2]=29;
    dmax=diaMes[this->mes];
    this->dia++;
    if (this->dia>dmax) { //si al incrementar dia superamos el numero de dias de dicho mes
        this->dia=1;      //pasamos a 1
        this->mes++;      //del mes siguiente
            if (this->mes>12) { //si al incrementar mes pasamos de 12 meses
                this->mes=1;    //pasamos al mes 1
                this->anio++;   //del año siguiente
            }
    }
    return copia; // Devuelvo la copia antes de ser incrementada.

}

Fecha& Fecha::operator++()
{

    int dmax,diaMes[]= {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(this->bisiesto())
        diaMes[2]=29;
    dmax=diaMes[this->mes];
    this->dia++;
    if(this->dia > dmax)
    {
        this->dia=1;
        this->mes++;
        if(this->mes > 12)
        {
            this->mes=1;
            this->anio++;
        }
    }
    return *this;
}

Fecha Fecha::operator+(const int &x)const
{

    Fecha f=*this;
    for(int j=0;j<x;j++)
        f++;
    return f;
}

Fecha Fecha::operator+(const Fecha& f)const{

Fecha incr=*this;
incr.dia+=f.dia;
incr.mes+=f.mes;
incr.anio+=f.anio;

return incr;

}

Fecha operator+(int x,const Fecha& f)
{
    Fecha fech=f;
    for(int j=0;j<x;j++)
        ++fech;
    return fech;
}

ostream& operator<<(ostream& s,const Fecha& f){

 char *nombreMes[] = {"error", "ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic"};
  if (f.dia < 10)
    s << "0";
  s << f.dia << " ";

  s << nombreMes[f.mes] << " " << f.anio;


return s;

}
Fecha::~Fecha()
{
    //dtor
}
