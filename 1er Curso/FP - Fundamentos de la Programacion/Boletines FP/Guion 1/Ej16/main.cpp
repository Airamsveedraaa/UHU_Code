#include <iostream>

using namespace std;

int main()
{
    int h,m,s,cantidad;
    cout << "Introduzca la cantidad de segundos a convertir: " << endl;
    cin >> cantidad;
    h=cantidad/3600;
    m=(cantidad%3600)/60;
    s= cantidad%60;
    cout << h << "hora " << m << "mins " << s << " segundos" << endl;
    return 0;
}
