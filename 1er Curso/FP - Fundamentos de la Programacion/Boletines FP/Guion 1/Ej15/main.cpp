#include <iostream>

using namespace std;

int main()
{
    int a,b,c,d,e,f;
    cout << "Introduzca los coeficientes a,b,c,d,e y f en ese orden: " << endl;
    cin >> a >> b >> c >> d >> e >> f;
    int x= ((c*e)-(b*f))/((a*e)-(b*d));
    int y= ((a*f)-(c*d))/((a*e)-(b*d));
    cout << "Sus coeficientes x e y son: "
         << "\nX: " << x
         << "\nY: " << y << endl;
    return 0;
}
