#include <iostream>

using namespace std;

int main()
{
    float N1,N2;
    cout << "Introduzca sus 2 numeros: " << endl;
    cin >> N1 >> N2;
    int suma= N1+N2;
    int resta= N1-N2;
    int multi= N1*N2;
    float divi= N1/N2;
    cout << "Resultados de las operaciones con sus numeros: "
         << "\nSuma: " << suma
         << "\nResta: " << resta
         << "\nMultiplicacion: " << multi
         << "\nDivision: " << divi << endl;
    return 0;
}
