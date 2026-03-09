#ifndef CLIENTE_H
#define CLIENTE_H
#include "Fecha.h"

class Cliente
{
private:
    long int dni;
    char* nombre;
    Fecha f;
    public:
        Cliente(long int dni,char* nombre,const Fecha& f);
        Cliente(const Cliente& c);
        void setNombre(const char* nombre);
        long int getDni()const{return this->dni;};
        const char* getNombre()const{return this->nombre;};
        Fecha getFecha()const{return this->f;};
        void setFecha(const Fecha& f);
        Cliente& operator=(const Cliente& c);
        bool operator==(const Cliente& c) const;
        friend ostream& operator<<(ostream& s,const Cliente& c);
        virtual ~Cliente();

};

ostream& operator<<(ostream& s,const Cliente& c);

#endif // CLIENTE_H
