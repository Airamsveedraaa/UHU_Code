#include <iostream>

using namespace std;

int main()
{
    int V[10];
    int max,min;
    for(int i=0; i<10; i++)
    {
        cout << "Introduzca el numero " << i+1 << endl;
        cin >> V[i];
    }
    max=V[0],min=V[0];
    for(int i=0; i<10; i++)
    {
        cout << V[i];
        cout << endl;
        if(V[i]<max)
            max=V[i];
        if(V[i]>min)
            min=V[i];
    }
    cout << "Maximo: " << max
         << "\nMinimo: " << min << endl;
    return 0;
}
