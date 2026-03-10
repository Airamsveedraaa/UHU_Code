#include <iostream>

using namespace std;

int main()
{
    float largo,ancho;
    cout << "Introduzca el largo y ancho del rectangulo: " << endl;
    cin >> largo >> ancho;
    float area= largo*ancho;
    float perimetro= (2*largo)+(2*ancho);
    cout << "Su rectangulo tendra de: "
         << "\nPerimetro: " << perimetro
         << "\nArea: " << area << endl;
    return 0;
}
