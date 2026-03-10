#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int N1,N2;
    char opcion;
    int suma,resta,multiplicacion;
    float division;
    do
    {
        cout << "        MENU        "
         << "\nA.Sumar"
         << "\nB.Restar"
         << "\nC.Multiplicar"
         << "\nD.Dividir"
         << "\nE.Salir"
         << "\nElija opcion: " << endl;
    cin >> opcion;
    system("cls");
    cin.ignore();
        switch(opcion)
        {
    case 'a':
    case 'A':

            cout << "Introduzca sus 2 numeros: " << endl;
            cin >> N1 >> N2;
            suma= N1+N2;
            cout << "Resultado: " << suma << endl;
            break;
    case 'b':
    case 'B':

            cout << "Introduzca sus 2 numeros: " << endl;
            cin >> N1 >> N2;
            resta= N1-N2;
            cout << "Resultado: " << resta << endl;
            break;
    case 'c':
    case 'C':

            cout << "Introduzca sus 2 numeros: " << endl;
            cin >> N1 >> N2;
            multiplicacion= N1*N2;
            cout << "Resultado: " << multiplicacion << endl;
            break;
    case 'd':
    case 'D':

            cout << "Introduzca sus 2 numeros: " << endl;
            cin >> N1 >> N2;
            division= N1/N2;
            cout << "Resultado: " << division << endl;
            break;
    case 'e':
    case 'E':
        cout << "Saliendo del menu..." << endl;
        break;
        default:
            cout << "Opcion incorrecta" << endl;
            break;
        }
    }
    while (opcion!='e' && opcion!='E');
    return 0;
}
