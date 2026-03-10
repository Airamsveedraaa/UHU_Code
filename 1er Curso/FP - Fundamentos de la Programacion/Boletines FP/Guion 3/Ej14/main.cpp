#include <iostream>

using namespace std;

int main()
{
    float V[15];
    int P;
    float menor=10000;
    int pos_menor;
    for(int i=0; i<15; i++)
    {
        cout << "Introduzca el numero " << i+1 << endl;
        cin >> V[i];
    }
    cout << "Desde que posicion quiere buscar el valor mas pequeno? " << endl;
    cin >> P;
    for(int i=P; i<15; i++)
    {
        if(V[i]<menor)
        {
            menor=V[i];
            pos_menor=i;
        }
    }
    cout << "Menor valor desde la posicion " << P << " es " << menor << " en la posicion " << pos_menor << endl;
    return 0;
}
