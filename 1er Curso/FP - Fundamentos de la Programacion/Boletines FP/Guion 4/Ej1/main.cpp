#include <iostream>

using namespace std;

void rellenar (int T[10]){

for(int i=0;i<10;i++){
    cout << "Introduce el numero " << i+1 << " del vector" << endl;
    cin >> T[i];
}

}

int minimo (int T[10]){

 int min=T[0];
    for(int i=0; i<10; i++)
    {
        if(T[i]<min)
            min=T[i];
    }
    return min;
}

int maximo (int T[10]){

    int max=T[0];
    for(int i=0; i<10; i++)
    {
        if(T[i]>max)
            max=T[i];
    }
    return max;
}
int main()
{
    int V[10];
    rellenar(V);
    int men=minimo(V);
    int max=maximo(V);
    cout << "El mayor numero es " << max
         << "\nY el menor es: " << men << endl;
    return 0;
}
