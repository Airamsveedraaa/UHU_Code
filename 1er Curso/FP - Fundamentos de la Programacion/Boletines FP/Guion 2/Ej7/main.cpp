#include <iostream>

using namespace std;

int main()
{
    int dist,Ndias,Edad;
    cout << "Introduzca la distancia a recorrer, el numero de dias que viajaray y la edad del pasajero: " << endl;
    cin >> dist >> Ndias >> Edad;
    int precio_sindesc= 0.75*dist;
    int desc= 0.25*precio_sindesc;
    int precio_final= precio_sindesc-desc;

    if(Ndias>7 && dist> 800 || Edad>55){
        cout << "Usted tiene derecho a un descuento en su viaje de: " << desc
             << "\nEl precio final de su viaje sera de: " << precio_final << "Euros" << endl;
    }
    else{
        cout << "Usted no tiene derecho a descuento, el precio de su viaje sera: " << precio_sindesc << endl;
    }
    return 0;
}
