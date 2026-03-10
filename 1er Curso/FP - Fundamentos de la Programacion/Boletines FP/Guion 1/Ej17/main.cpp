#include <iostream>

using namespace std;

int main()
{
    int longitud_en_metros;
    cout << "Introduzca la longitud en metros: " << endl;
    cin >> longitud_en_metros;
    int Precio_tota_en_euros=5000 * (longitud_en_metros / 5280.0);
    cout << "El presupuesto sera de: " << Precio_tota_en_euros << " Euros" << endl;
    return 0;
}
//No da el mismo resultado porque la division en una no da el valor verdadero de la division
