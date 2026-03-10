#include <iostream>
#include <windows.h>
#define MAX_CUENTAS 100
typedef char Cadena[50];

using namespace std;

class Cuenta //Contiene los datos de una cuenta bancaria
{
private:
    float Saldo;
    int NoCuenta;
    bool Bloqueada;
public:
    Cuenta();
    Cuenta(int pNo, float pSal);
    bool ActualizarSaldo(int pSal);
    void ActualizarBloqueo(bool pBloq);
    float DameSaldo();
    int DameNoCuenta();
    bool EstaBloqueada();
};


Cuenta::Cuenta()
{

    Saldo=0;
    NoCuenta=0;
    Bloqueada=false;

}

Cuenta::Cuenta(int pNo, float pSal)
{

    Saldo=pSal;
    NoCuenta=pNo;
    Bloqueada=false;


}


bool Cuenta::ActualizarSaldo(int pSal)
{

    bool puedes=true;
    if(Bloqueada)
    {
        puedes=false;
    }
    else
        Saldo=pSal;

    return puedes;


}

void Cuenta::ActualizarBloqueo(bool pBloq)
{

    Bloqueada=pBloq;

}

float Cuenta::DameSaldo()
{

    return Saldo;

}

int Cuenta::DameNoCuenta()
{

    return NoCuenta;

}

bool Cuenta::EstaBloqueada()
{
    return Bloqueada;

}

int BuscarCuenta(Cuenta Ctas[MAX_CUENTAS],int Ncuentas, int NoCuenta)
{

    int pos=-1;
    int i=0;
    while(i<Ncuentas && pos==-1)
    {
        if(Ctas[i].DameNoCuenta()==NoCuenta)
        {
            pos=i;
        }
        else
            i++;
    }
    return pos;

}

int MenuCuentas()
{

    int opc;
    cout << "     Menu Gestion de cuentas     "
         << "\n1. Anadir una cuenta a un cliente"
         << "\n2. Mostrar las cuentas del cliente"
         << "\n3. Borrar una cuenta del cliente"
         << "\n4. Modificar saldo de una cuenta"
         << "\n5. Modificar estado de una cuenta"
         << "\n6. Salir"
         << "\nElige opcion: " << endl;
    cin >> opc;
    cin.ignore();
    system("cls");

    return opc;
}

int main()
{
    Cuenta DatosCuentas[MAX_CUENTAS];
    int nCuentas = 0;
    int numcuenta;
    float saldo;
    int opc;
    int pos;
    char c;
    do
    {
        opc=MenuCuentas();
        switch(opc)
        {

        case 1:

            if(nCuentas>=MAX_CUENTAS)
            {
                cout << "No se pueden añadir mas cuentas" << endl;
            }
            else
            {
                cout << "Dame el numero de cuenta: " << endl;
                cin >> numcuenta;
                cout << "Dame el saldo de la cuenta" << endl;
                cin >> saldo;

                DatosCuentas[nCuentas]=Cuenta(numcuenta,saldo);
                nCuentas++;
                cout << "Cuenta añadida" << endl;

            }
            break;

        case 2:
            cout << "INFORMACION CUENTAS: " << endl;
            for(int i=0; i<nCuentas; i++)
            {
                cout << "NUMERO: " << DatosCuentas[i].DameNoCuenta()
                     << "\nSALDO: " << DatosCuentas[i].DameSaldo()
                     << "\nBLOQUEADA? " << (DatosCuentas[i].EstaBloqueada() ? "si" : "no") << endl;
            }
            break;

        case 3:
            cout << "Introduzca el numero de cuenta a eliminar: " << endl;
            cin >> numcuenta;
            pos=BuscarCuenta(DatosCuentas,nCuentas,numcuenta);
            if(pos==-1)
            {
                cout << "Cuenta no existente" << endl;
            }
            else
            {
                for(int i=pos; i<nCuentas; i++)
                {
                    DatosCuentas[i]=DatosCuentas[i+1];
                }

                nCuentas--;
                cout << "Cuenta eliminada" << endl;
            }
            break;

        case 4:

            cout << "Introduzca el numero de cuenta: " << endl;
            cin >> numcuenta;
            pos=BuscarCuenta(DatosCuentas,nCuentas,numcuenta);
            if (pos == -1)
            {
                cout << "Cuenta no existente" << endl;
            }
            else
            {
                cout << "Ingrese el saldo: ";
                cin >> saldo;

                if (DatosCuentas[pos].ActualizarSaldo(saldo))
                {
                    cout << "Saldo actualizado correctamente." << endl;
                }
                else
                {
                    cout << "No se pudo actualizar el saldo porque la cuenta está bloqueada." << endl;
                }
            }
            break;

        case 5:

            cout << "Ingrese el numero de cuenta : " << endl;
            cin >> numcuenta;
            pos=BuscarCuenta(DatosCuentas,nCuentas,numcuenta);
            if(pos==-1){
                cout << "Cuenta no existente" << endl;
            }
            else{
                cout << "Desea actualizar el estado de bloqueo? s/n" << endl;
                cin >> c;
                if(c=='s'){
                    bool nuevoestado=!DatosCuentas[pos].EstaBloqueada();
                    DatosCuentas[pos].ActualizarBloqueo(nuevoestado);
                    cout << "Estado de la cuenta actualizado" << endl;
                }
                    else
                        cout << "No se ha actualizado el estado de la cuenta" << endl;

            }
            break;

        case 6:
            cout << "Saliendo del menu..." << endl;
            break;

        default:
            cout << "OPCION INCORRECTA" << endl;
            break;

        }
    }
    while(opc!=6);
    return 0;
}
