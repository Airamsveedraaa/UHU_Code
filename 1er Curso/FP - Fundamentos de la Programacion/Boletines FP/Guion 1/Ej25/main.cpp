#include <iostream>
#include <cmath>
#define g 9.8
using namespace std;

int main()
{
    float m,v,h;
    cout << "Introduzca la masa, velocidad y altura del cuerpo: " << endl;
    cin >> m >> v >> h;
    v=v*(1000/3600.0);
    h=h*1000;
    float Ec= (1.0/2)*(m*pow(v,2));
    float Ep= m*g*h;
    float Em= Ec+Ep;
    cout << "Resultados: "
         << "\nCinetica: " << Ec << "J"
         << "\nPotencial: " << Ep << "J"
         << "\nMecanica: " << Em << "J" << endl;
    return 0;
}
