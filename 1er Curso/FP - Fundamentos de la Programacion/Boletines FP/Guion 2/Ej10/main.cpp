#include <iostream>

using namespace std;

int main()
{
    int N,mayor,menor,media,numero;
    int suma=0;
    cout << "Cuantos numeros desea introducir? " << endl;
    cin >> N;
    for(int i=0;i<N;i++){
        cout << "Introduzca el numero " << i+1<< endl;
        cin >> numero;
        if(numero>mayor){
            mayor=numero;
        }
        if(numero<menor){
            menor=numero;
        }
        suma+=numero;
    }
    media=suma/N;
    cout << "La media es: " << media
         << "\nEl mayor es: " << mayor
         << "\nY el menor es: " << menor << endl;
    return 0;
}
