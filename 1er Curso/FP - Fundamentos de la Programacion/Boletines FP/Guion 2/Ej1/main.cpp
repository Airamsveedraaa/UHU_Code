#include <iostream>

using namespace std;

int main()
{
    float Nota;
    cout << "Introduzca su nota obtenida: " << endl;
    cin >> Nota;
    if(Nota<0 || Nota >10)
        cout << "Error en la nota" << endl;
    else if (Nota >=0 && Nota < 5)
        cout << "Suspenso" << endl;
    else if(Nota>=5 && Nota <7)
        cout << "Aprobado" << endl;
    else if(Nota>=7 && Nota <9)
        cout << "Notable" << endl;
    else if(Nota>=9 && Nota <=10)
        cout << "Sobresaliente" << endl;
    return 0;
}
