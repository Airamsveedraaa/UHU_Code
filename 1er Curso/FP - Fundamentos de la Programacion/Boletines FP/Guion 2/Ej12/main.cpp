#include <iostream>

using namespace std;

int main()
{
    int N;
    do{
    cout << "Introduzca el numero [0,10]" << endl;
    cin >> N;
    if(N<1 || N>10)
        cout << "Error, debe estar entre 0 y 10" << endl;
    }while(N<1 || N>10);
    cout << "Tabla de multiplicar: " << endl;
    for (int i=0;i<=10;i++){
        cout << i*N;
        cout << endl;
    }
    return 0;
}
