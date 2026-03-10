#include <iostream>
#define libra 0.84
#define dolar 1.04
using namespace std;

int main()
{
    float E,D,L;
    cout << "Introduzca la cantidad en euros a convertir: " << endl;
    cin >> E;
    D=E*dolar;
    L=E*libra;

    cout << "Su cantidad convertida es: "
         << "\nDolares: " << D
         << "\nLibras: " << L << endl;
    return 0;
}
