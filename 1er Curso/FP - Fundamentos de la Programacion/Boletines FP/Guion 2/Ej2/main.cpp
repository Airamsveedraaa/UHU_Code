#include <iostream>

using namespace std;

int main()
{
    int N1,N2;
    cout << "Introduzca los 2 numeros a comparar: " << endl;
    cin >> N1 >> N2;
    if(N1>N2)
        cout << "El primer numero es mayor y el segundo es menor" << endl;
    else if (N1<N2)
        cout << "El segundo numero es mayor y el primero es menor" << endl;
    else
        cout << "Los dos numeros son iguales" << endl;
    return 0;
}
