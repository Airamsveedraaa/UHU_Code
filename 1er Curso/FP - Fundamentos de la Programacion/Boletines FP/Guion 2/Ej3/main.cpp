#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a,b,c;
    cout << "Introduzca los coeficientes a b y c: " << endl;
    cin >> a >> b >> c;
    float discrminante= pow(b,2) - (4*a*c);
    float ec1= (-b+(sqrt(discrminante)))/(2*a);
    float ec2= (-b-(sqrt(discrminante)))/(2*a);
    if(discrminante<0)
    {
        cout << "No tiene soluciones reales" << endl;
    }

    if(discrminante > 0 && ec1<0)
    {
        cout << "Tiene una solucion y es: " << ec2 << endl;
    }
    else if(discrminante > 0 && ec2<0)
    {
        cout << "Tiene una solucion y es: " << ec1 << endl;
    }
    else if (discrminante > 0 && ec1>0 && ec2>0)
        cout << "Tiene dos soluciones y son: " << ec1 << " " << ec2 << endl;
    return 0;
}
