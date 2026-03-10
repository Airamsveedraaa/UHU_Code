#include <iostream>

using namespace std;

int main()
{
    int N1,N2;
    char op;
    cout << "Introduzca sus 2 numeros: " << endl;
    cin >> N1 >> N2;
    cout << "Que operacion desea realizar con ellos? (s/r)" << endl;
    cin >> op;
    if(op=='s' || op=='S' || op=='+'){
        int suma= N1+N2;
        cout << "Resultado: " << suma << endl;
    }
    else if (op=='r' ||op=='R' || op=='-'){
        int resta= N1-N2;
        cout << "Resultado: " << resta << endl;
    }
    else
        cout << "Operacion no disponible" << endl;
    return 0;
}
