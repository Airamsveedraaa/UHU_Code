#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef char Cadena[50];

class Vehiculo
{

private:
    Cadena Identificador;
    int Controles[100];
    int NoControles;
public:
    Vehiculo();
    int NumeroControles();
    void PonerIdent(Cadena pIdent);
    void DameIdent(Cadena pIdent);
    int DameVelocidad(int pNoControl);
    void GenerarControles(int pNControles);
    void ControlVelocidad(int &pPos);


};

Vehiculo::Vehiculo()
{

    strcpy(Identificador,"NO HAY IDENTIFICADOR");
    NoControles=0;

}

int Vehiculo::NumeroControles()
{

    return NoControles;

}

void Vehiculo::PonerIdent(Cadena pIdent)
{

    strcpy(Identificador,pIdent);

}


void Vehiculo::DameIdent(Cadena pIdent)
{

    strcpy(pIdent,Identificador);

}

int Vehiculo::DameVelocidad(int pNoControl) {
    int i = 0;
    int velocidad = 0;

    while (i < NoControles && velocidad == 0) {
        if (i == pNoControl) {
            velocidad = Controles[i];
        } else {
            i++;
        }
    }

    return velocidad;
}

void Vehiculo::GenerarControles(int pNControles)
{
    NoControles=pNControles;
    for(int i=0; i<pNControles; i++)
    {
        Controles[i]=10+(rand()%301);
    }

}

void Vehiculo::ControlVelocidad(int &pPos)
{

    int menor=310;
    for(int i=0; i<NoControles; i++)
    {
        if(Controles[i]<menor)
        {
            menor=Controles[i];
            pPos=i;
        }
    }
}

int BuscarVehiculo(Vehiculo pVehiculos[200], int pNVehiculos, int pVMin, int &pPosC) {
    int i = 0;
    int vehiculoPos = -1;
    pPosC = -1;
    bool encontrado = false; // Bandera para salir de ambos bucles

    while (i < pNVehiculos && !encontrado) {
        int j = 0;
        while (j < pVehiculos[i].NumeroControles() && !encontrado) {
            if (pVehiculos[i].DameVelocidad(j) < pVMin) {
                pPosC = j;
                vehiculoPos = i;
                encontrado = true; // Se encontró, salimos de los bucles
            } else {
                j++;
            }
        }
        i++;
    }

    return vehiculoPos;
}
int main()
{
    srand(time(0));
    Vehiculo Participantes[200];
    int nVehiculos;
    int Vmin=30;
    int pos;
    int NControl=5+(rand()%10);

    cout << "Cuantos vehiculos desea añadir? " << endl;
    cin >> nVehiculos;
    cin.ignore();
    for(int i=0; i<nVehiculos; i++)
    {
        Cadena identificador;
        cout << "Introduzca el identificador del vehiculo " << i+1 << endl;
        cin.getline(identificador,50);

        Participantes[i].PonerIdent(identificador);
        Participantes[i].GenerarControles(NControl);
    }

        int Posvehi=BuscarVehiculo(Participantes,nVehiculos,Vmin,pos);
        if(Posvehi==-1)
        {
            cout << "No se ha encontrado ningun vehiculo" << endl;

        }

        else
        {

            Cadena identificadorEnc;
            Participantes[Posvehi].DameIdent(identificadorEnc);
            cout << "El vehiculo con el identificador " << identificadorEnc
                 << "\nha registrado una velocidad inferior a 30 en el punto de control "
                 << "\n" << pos
                 << "\ny su velocidad fue de: " << Participantes[Posvehi].DameVelocidad(pos) << endl;
        }
        return 0;
    }


