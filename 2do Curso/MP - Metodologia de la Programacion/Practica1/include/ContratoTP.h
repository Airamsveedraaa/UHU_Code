#ifndef CONTRATOTP_H
#define CONTRATOTP_H
#include <Contrato.h>


class ContratoTP : public Contrato
{
private:
    static float precioTP;
    static int minutosTP;
    int minutosHablados;
    static const float precioExcesoMinutos;
public:
    ContratoTP(long int dni,const Fecha& f,int m);
    virtual ~ContratoTP();
    ContratoTP(const ContratoTP& c);
    static int getLimiteMinutos(){return ContratoTP::minutosTP;};
    static float getPrecio(){return ContratoTP::precioTP;};
    static void setTarifaPlana(int m,float p){ContratoTP::minutosTP=m; ContratoTP::precioTP=p;};
    int getMinutosHablados()const{return minutosHablados;};
    void setMinutosHablados(int m){minutosHablados=m;};
    void ver()const;
    float factura()const;
    friend ostream& operator<<(ostream& s,const ContratoTP& c);
};

    ostream& operator<<(ostream& s,const ContratoTP& c);

#endif // CONTRATOTP_H
