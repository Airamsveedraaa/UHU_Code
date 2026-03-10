#include <iostream>

using namespace std;

void rellenar(int T[10]){

for(int i=0;i<10;i++){
    cout << "Introduce el numero " << i+1 << " del vector" << endl;
    cin >> T[i];
}

}

bool buscar (int T[10],int x){

bool encontrado=false;
int i=0;
while(i<10 && !encontrado)
    if(i==x)
    encontrado=true;
else
    i++;

    return encontrado;

}
int main()
{
    int V[10],x;
    rellenar(V);
    cout << "Introduce el numero X a buscar: " << endl;
    cin >> x;
    if(buscar(V,x)){
        cout << "El numero pertenece al vector" << endl;
    }
    else
        cout << "El numero no pertenece al vector" << endl;
    return 0;
}
