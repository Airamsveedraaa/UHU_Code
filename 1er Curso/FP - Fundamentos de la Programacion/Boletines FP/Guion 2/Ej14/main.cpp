#include <iostream>

using namespace std;

int main()
{
    int N;
    long fact=1;
    do{
    cout << "Introduzca el numero (1-20): " << endl;
    cin >> N;
    if(N<0 || N>=20)
        cout << "Error, debe ser positivo y menor que 20" << endl;
    }while(N <0 || N > 20);
    for(int i=1;i<=N;i++)
    {
        fact=fact*i;
    }
    cout << "El resultado es: " << fact << endl;
    return 0;
}
