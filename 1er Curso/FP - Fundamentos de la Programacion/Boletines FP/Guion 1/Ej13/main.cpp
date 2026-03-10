#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a,b,c;
    cout << "Introduzca los coeficientes a b y c: " << endl;
    cin >> a >> b >> c;
    float discrminante= pow(b,2) - (4*a*c);
    float ec1= (-b+(discrminante))/(2*a);
    float ec2= (-b-(discrminante))/(2*a);
    cout << "Las solciones a su ecuacion es: " << ec1 << " " << ec2 << endl;
    return 0;
}
