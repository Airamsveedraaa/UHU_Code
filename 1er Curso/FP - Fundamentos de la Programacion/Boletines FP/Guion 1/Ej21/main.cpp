#include <iostream>

using namespace std;

int main()
{
    int a,b,c,d;
    int Nsum,Dsum,Nres,Dres,Nmul,Dmul,Ndiv,Ddiv;
    cout << "Introduzca sus coeficientes a,b,c y d: " << endl;
    cin >> a >> b >> c >> d;
    Nsum= (a*d)+(b*c);
    Dsum= b*d;
    Nres=(a*d)-(b*c);
    Dres=b*d;
    Nmul=a*c;
    Dmul=b*d;
    Ndiv=a*d;
    Ddiv=b*c;
    cout << "Resultados: "
         << "\nSuma: " << Nsum << "/" << Dsum
         << "\nResta: " << Nres << "/" << Dres
         << "\nMultiplicacion: " << Nmul << "/" << Dmul
         << "\nDivision: " << Ndiv << "/" << Ddiv << endl;
    return 0;
}
