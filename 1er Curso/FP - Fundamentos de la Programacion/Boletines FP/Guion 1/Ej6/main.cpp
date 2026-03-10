#include <iostream>

using namespace std;

int main()
{
    int Nt,Np,Ntotal;
    cout << "Introduzca su nota de teoria y de practicas: " << endl;
    cin >> Nt >> Np;
    Ntotal= (Nt*0.4)+(Np*0.6);
    cout << "Su nota total es: " << Ntotal << endl;
    return 0;
}
