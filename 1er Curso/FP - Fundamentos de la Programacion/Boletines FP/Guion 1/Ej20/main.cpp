#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    float V,V0,a,t,S0,S;
    cout << "Introduzca la velocidad inicial (V0), la posicion inicial (S0), la aceleracion (a) y el tiempo (t): " << endl;
    cin >> V0 >> S0 >> a >> t;
    V=V0+(a*t);
    S=S0+((V0*t)+((1.0/2)*a*pow(t,2)));
    cout << "La velocidad final sera de: " << V << " m/s"
         << "\Y la distancia recorrida sera de : " << S << " m" << endl;
    return 0;
}
