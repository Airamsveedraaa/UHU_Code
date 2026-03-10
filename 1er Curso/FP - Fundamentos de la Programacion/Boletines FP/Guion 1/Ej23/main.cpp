#include <iostream>
#include <cmath>
#define k 9e9
using namespace std;

int main()
{
    float q1,q2,r;
    cout << "Introduzca sus cargas q1 y q2 y la distancia r entre ellas: " << endl;
    cin >> q1 >> q2 >> r;
    q1=q1*1e-6;
    q2=q2*1e-6;
    float F=k*((q1*q2)/pow(r,2));
    cout << "La fuerza de atraccion/repulsion de sus cargas es de: " << F << "N" << endl;
    return 0;
}
