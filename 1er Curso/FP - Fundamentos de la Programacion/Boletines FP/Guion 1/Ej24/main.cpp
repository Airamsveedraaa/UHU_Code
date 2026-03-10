#include <iostream>
#include <cmath>
#define P 8.85e-12
#define pi 3.14
using namespace std;

int main()
{
    float q,r;
    cout << "Introduzca el valor de la carga y su distancia r: " << endl;
    cin >> q >> r;
    q=q*1e-6;
    float E= q/(4*pi*P*pow(r,2));
    cout << "La intensidad del campo electrico generado por la carga q a la distancia r es de : "
         << "\n" << E << "N/C" << endl;
    return 0;
}
