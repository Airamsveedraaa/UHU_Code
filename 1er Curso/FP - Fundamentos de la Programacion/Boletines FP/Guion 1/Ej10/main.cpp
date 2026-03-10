#include <iostream>
#include <cmath>
#define PI 3.14
using namespace std;

int main()
{
    float r;
    cout << "Introduzca el radio de su circunferencia: " << endl;
    cin >> r;
    float longitud= 2*PI*r;
    float superficie= PI* pow(r,2);
    float volumen= (4*PI*pow(r,3))/3;
    cout << "Los resultados son: "
         << "\nLongitud: " << longitud
         << "\nSuperficie: " << superficie
         << "\nVolumen: " << volumen << endl;
    return 0;
}
