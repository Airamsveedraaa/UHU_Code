#include <iostream>

using namespace std;

int main()
{
    int Cels,Fare;
    cout << "Introduzca su temperatura en Celsius: " << endl;
    cin >> Cels;

    Fare= (9.0/5)*Cels+32;

    cout << "Su temperatura en Farenheit es: " << Fare << endl;
    return 0;
}
