#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int N1,N2;
    int opcion;
    int suma,resta,multiplicacion;
    float division;
    do
    {
        cout << "        MENU        "
         << "\n1.Sumar"
         << "\n2.Restar"
         << "\n3.Multiplicar"
         << "\n4.Dividir"
         << "\nElija opcion: " << endl;
    cin >> opcion;
    system("cls");
    cin.ignore();
        switch(opcion)
        {
        case 1:
            cout << "Introduzca sus 2 numeros: " << endl;
            cin >> N1 >> N2;
            suma= N1+N2;
            cout << "Resultado: " << suma << endl;
            break;
        case 2:
            cout << "Introduzca sus 2 numeros: " << endl;
            cin >> N1 >> N2;
            resta= N1-N2;
            cout << "Resultado: " << resta << endl;
            break;
        case 3:
            cout << "Introduzca sus 2 numeros: " << endl;
            cin >> N1 >> N2;
            multiplicacion= N1*N2;
            cout << "Resultado: " << multiplicacion << endl;
            break;
        case 4:
            cout << "Introduzca sus 2 numeros: " << endl;
            cin >> N1 >> N2;
            division= N1/N2;
            cout << "Resultado: " << division << endl;
            break;
        default:
            cout << "Opcion incorrecta" << endl;
            break;
        }
    }
    while (opcion!=4);
    return 0;
}
