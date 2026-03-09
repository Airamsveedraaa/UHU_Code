#ifndef CONTRATO_H
#define CONTRATO_H
#include "Comun.h"
#include "Fecha.h"
class Contrato
{
private:
    static int contador;
    const int idContrato;
    long int dniContrato;
    Fecha fechaContrato;
    public:
        Contrato(long int dni,const Fecha& fechaContrato);
        Contrato(const Contrato &c);
        virtual ~Contrato();
        virtual void ver()const;
        virtual float factura()const=0;
        int getIdContrato()const{return this->idContrato;};
        long int getDniContrato() const{return this->dniContrato;};
        const Fecha& getFechaContrato() const{return this->fechaContrato;};
        void setDniContrato( long int dni){this->dniContrato=dni;};
        void setFechaContrato(const Fecha& f){this->fechaContrato.setFecha(f.getDia(),f.getMes(),f.getAnio());};
        friend ostream& operator<<(ostream& s,const Contrato& c);

};
ostream& operator<<(ostream& s,const Contrato& c);
#endif // CONTRATO_H
