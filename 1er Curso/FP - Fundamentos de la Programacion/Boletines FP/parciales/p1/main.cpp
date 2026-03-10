#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#define MAX_VEHI 35
#define NDIAS 10
using namespace std;

int main()
{
    srand(time(0));
    int NumVe;
    int Matriculas [MAX_VEHI];
    float Distancia [MAX_VEHI][NDIAS];
    int opc,matricula_busc;
    bool encontrado=false;
    do
    {

        cout << "     MENU     "
             << "\n1.Introducir datos vehiculos"
             << "\n2.Mostrar datos vehiculos"
             << "\n3.Consultar consumos"
             << "\n4.Salida"
             << "\nElige opcion: " << endl;
        cin >> opc;
        cin.ignore();
        system("cls");

        switch(opc)
        {

        case 1:

            do
            {
                cout << "Cuantos vehiculos hay alquilados? " << endl;
                cin >> NumVe;
                if(NumVe<1 || NumVe>35)
                {
                    cout << "Error, debe estar entre 1 y 35" << endl;
                }
            }
            while(NumVe<1 || NumVe>35);

            for(int i=0; i<NumVe; i++)
            {
                cout << "Introduzca la matricula del vehiculo " << i+1 << endl;
                cin >> Matriculas[i];
                for(int j=0; j<NDIAS; j++)
                {
                    Distancia[i][j]=100+(rand()%6510/10.0);
                }
            }
            break;

        case 2:
            for(int i=0; i<NumVe; i++)
            {
                cout << "Matricula" << Matriculas[i] << ":";
                for(int j=0; j<NDIAS; j++)
                {
                    cout << Distancia[i][j];
                    if(j<NDIAS-1)
                    {
                        cout << ",";
                    }
                    else
                        cout << ".";
                }
                cout << endl;
            }
    break;

case 3:
    {

        cout << "Introduzca la matricula a buscar: " << endl;
        cin >> matricula_busc;
        int i=0;
        while(i<NumVe && !encontrado)
        {
            if(Matriculas[i]==matricula_busc)
            {
                encontrado=true;
            }
            i++;
        }
        if(encontrado)
        {
            float consumo_total=0.0;
            for(int j=0; j<NDIAS; j++)
            {
                if((j+1)%2==0)
                {
                    consumo_total+=Distancia[i][j]/8.1;
                }
                else
                    consumo_total+=Distancia[i][j]/7.4;
            }
            cout << "Matricula encontrada, informacion de consumo: "
                 << "\nmatricula: " << matricula_busc
                 << "\nconsumo: " << consumo_total << "l/km" << endl;
        }
        else
        {
            cout << "Matricula no encontrada" << endl;
        }
    }
    break;

case 4:
    cout << "Saliendo del programa..." << endl;
    break;

default:
    cout << "Opcion incorrecta." << endl;
    break;

}
}
while(opc!=4);
return 0;
}
