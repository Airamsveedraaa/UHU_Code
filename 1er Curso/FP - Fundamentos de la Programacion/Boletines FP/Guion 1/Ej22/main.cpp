#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a,b,c,d;
    int sumR,sumI,resR,resI,mulR,mulI,divR,divI;
    cout << "Introduzca sus coeficientes a,b,c y d: " << endl;
    cin >> a >> b >> c >> d;
    sumR=a+c;
    sumI=b+d;
    resR=a-c;
    resI=b-d;
    mulR=(a*c)-(b*d);
    mulI=(a*d)+(b*c);
    divR=((a*c)+(b*d))/(pow(c,2)+pow(d,2));
    divI=((b*c)-(a*d))/(pow(c,2)+pow(d,2));
    cout << "Resultados: "
         << "\nSuma: " << sumR << "," << sumI << "i"
         << "\nResta: " << resR << "," << resI << "i"
         << "\nMultiplicacion: " << mulR << "," << mulI << "i"
         << "\nDivision: " << divR << "," << divI << "i" << endl;
    return 0;
}
