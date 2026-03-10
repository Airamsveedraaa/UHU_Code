#include <iostream>

using namespace std;
typedef char cadena[30];
struct persona
{
    int dni; //DNI de la persona sin letra
    cadena nombre; //Nombre de la persona
};

void rellenar (persona T[2][4]){



for(int i=0;i<2;i++){
    for(int j=0;j<4;j++){
        cout << "Introduzca el dni de la persona " << i << ", " << j << endl;
        cin >>  T[i][j].dni;
        cout << "Ahora introduzca el nombre de la persona " << i << ", " << j << endl;
        cin >> T[i][j].nombre;
    }
}

}

bool  buscar (persona T[2][4], long dni, int &f, int &c){

bool encontrado=false;
int i=0;
while(i<2 && !encontrado){
    int j=0;
    while(j<4 && !encontrado){
        if(T[i][j].dni==dni){
            encontrado=true;
            f=i;
            c=j;
        }
        else
            j++;
    }
    i++;
}

return encontrado;
}
int main()
{
    persona P[2][4];
    long dni_buscar;
    int f,c;
        rellenar(P);
        cout << "Introduzca el dni de la persona a buscar" << endl;
        cin >> dni_buscar;
        if(buscar(P,dni_buscar,f,c)){
            cout << "Se ha encontrado a la persona, se encuentra en la posicion " << f << "," << c
                 << "\ny sus datos son: "
                 << "\nDni: " << P[f][c].dni
                 << "\nNombre: " << P[f][c].nombre << endl;
        }
        else
            cout << "No se ha encontrado a la personsa con ese dni" << endl;
    return 0;
}
