#include <iostream>

using namespace std;

int main()
{
    int a,b;
    cout << "Inntroduzca las variables a intercambiar: " << endl;
    cin >> a >> b;
    int temp=a;
    a=b;
    b=temp;
    cout << "Sus numeros han sido intercambiados, ahora son: " << a << " " << b << endl;
    return 0;
}
