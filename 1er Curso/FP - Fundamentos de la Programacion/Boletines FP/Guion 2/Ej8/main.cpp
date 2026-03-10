#include <iostream>
#include <cmath>
#include <windows.h>
#define pi 3.14
#define P 8.85e-12
using namespace std;

int main()
{
    char unidad_carga;
    int unidad_dist;
    float q,r;
    cout << "Introduzca el valor de la carga: " << endl;
    cin >> q;
        cout << "En que unidad desea trabajar la carga? "
             << "\nA.Miliculombios(10^-3)"
             << "\nB.Microculombios(10^-6)"
             << "\nC.Nanoculombios(10^-9)"
             << "\nSi elige una incorrecta se asumira la unidad por defecto (Microcolumbios)"
             << "\nElija unidad: " << endl;
        cin >> unidad_carga;
        cin.ignore();
        system("cls");
        switch(unidad_carga)
        {
        case 'A':
        case 'a':
            cout << "Ha elegido Miliculombios" << endl;
            q=q*1e-3;
            break;
        case 'B':
        case 'b':
            cout << "Ha elegido Microculombios" << endl;
            q=q*1e-6;
            break;
        case 'C':
        case 'c':
            cout << "Ha elegido Nanoculombios" << endl;
            q=q*1e-9;
            break;
        default:
            cout << "Se ha elegido la unidad por defecto (Microculombio)" << endl;
            break;
        }

    cout << "Introduzca ahora la distancia r: " << endl;
    cin >> r;
         cout << "En que unidad desea trabajar la distancia? "
             << "\n1.Decimetros (dm)"
             << "\n2.Centimetros (cm)"
             << "\n3.Milimetros (mm)"
             << "\nDe no elegir opcion o elegir una incorrecta se usara la unidad por defecto (m)"
             << "\nElija opcion: " << endl;
        cin >> unidad_dist;
        cin.ignore();
        system("cls");
        switch(unidad_dist)
        {

        case 1:
            cout << "Ha elegido Decimetros" << endl;
            r=r/10;
            break;
        case 2:
            cout << "Ha elegido Centimetros" << endl;
            r=r/100;
            break;
        case 3:
            cout << "Ha elegido Milimetros" << endl;
            r=r/1000;
            break;
        default:
            cout << "Se ha elegido la unidad por defecto (m)" << endl;
            break;
        }
    float E= q/(4*pi*P*pow(r,2));
    cout << "La intensidad del campo electrico generado por la carga q a la distancia r es de : "
         << "\n" << E << "N/C" << endl;
    return 0;
}
