#ifndef FECHA_H
#define FECHA_H
#include "Comun.h"

class Fecha
{
private:
    int dia,mes,anio;
    public:
        Fecha(int dia, int mes,int anio);
        void setFecha(int dia, int mes, int anio);
        int getDia()const{return this->dia;};
        int getMes()const{return this->mes;};
        int getAnio()const{return this->anio;};
        void ver()const;
        bool bisiesto()const;
        Fecha operator++(int i);
        Fecha& operator++();
        Fecha operator+(const int &x)const;
        Fecha operator+(const Fecha& f)const;
        friend Fecha operator+(int x,const Fecha& f);
        friend ostream& operator<<(ostream& s,const Fecha& f);
        virtual ~Fecha();
};

 Fecha operator+(int x,const Fecha& f);
 ostream& operator<<(ostream& s,const Fecha& f);
#endif // FECHA_H
