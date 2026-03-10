#include <iostream>

using namespace std;

int main()
{
    float N1,N2,N3,N4,N5;
    cout << "Introduzca las 5 notas obtenidas: " << endl;
    cin >> N1 >> N2 >> N3 >> N4 >> N5;
    float Media= (N1+N2+N3+N4+N5)/5;
    cout << "Su nota media obtenida es: " << Media << endl;
    return 0;
}
