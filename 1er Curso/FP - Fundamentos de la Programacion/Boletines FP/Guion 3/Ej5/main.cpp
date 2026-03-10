#include <iostream>

using namespace std;
typedef char cadena[30];
struct persona
{
    int dni; //DNI de la persona sin letra
    cadena nombre; //Nombre de la persona
};

int main()
{
    persona T[2][4];
    bool encontrado=false;
    int dni_buscar;
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout << "Introduzca el nombre de la persona " << i << " " << j << endl;
            cin >> T[i][j].nombre;
            cout << "Introduzca el DNI de la persona " << i << " " << j << endl;
            cin >> T[i][j].dni;
        }
    }
    cout << "Introduzca el dni a buscar" << endl;
    cin >> dni_buscar;
    int i=0,j;
    while(i<2 && !encontrado)
    {
        j=0;
        while(j<4 && !encontrado)
        {
            if(dni_buscar==T[i][j].dni)
            {
                cout << "Se ha encontrado a la persona, mostrando datos: "
                     << "\nNombre: " << T[i][j].nombre
                     << "\nDni: " << T[i][j].dni << endl;
                encontrado=true;
            }
            else
                j++;
        }
        i++;
    }
   if(!encontrado)
        cout << "No se ha encontrado a la persona " << endl;
    return 0;
}
