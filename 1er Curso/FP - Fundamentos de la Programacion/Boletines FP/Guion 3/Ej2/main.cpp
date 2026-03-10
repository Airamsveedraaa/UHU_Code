#include <iostream>

using namespace std;

int main()
{
    int V[10];
    int X,j=0;
    bool encontrado;
//Sistema de recorrido para rellenar vector
for(int i=0;i<10;i++){
    cout << "Introduzca el numero " << i+1 << endl;
    cin >> V[i];
}
cout << "Introduzca su valor X a buscar en el vector :" << endl;
cin >> X;
//Sistema de busqueda
while(j<10 && !encontrado){
    if(X==V[j]){
        encontrado=true;
    }
    else
        j++;
}
if(encontrado)
    cout << "Su numero X se encuentra en el vector" << endl;
else
    cout << "Su numero X no se encuentra en el vector" << endl;
    return 0;
}
