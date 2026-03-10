#include <iostream>

using namespace std;

int main()
{
    float n;
    cout << "Introduzca su cantidad de bytes a convertir: " << endl;
    cin >> n;
    n=n/1024;
    cout << "Tiene " << n << " Kbytes " << endl;
    return 0;
}
