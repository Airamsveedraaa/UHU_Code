#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int x1,y1,x2,y2;
    cout << "Introduzca las coordenadas x e y del primer punto y luego las del segundo: " << endl;
    cin >> x1 >> y1 >> x2 >> y2;
    float distancia= sqrt(pow(x2-x1,2) + pow(y2-y1,2));
    cout << "La distancia entre sus puntos es: " << distancia << endl;
    return 0;
}
