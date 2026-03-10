#include <iostream>
#include <cstring>
using namespace std;

typedef char cadena[100];
int main()
{
    cadena Nombre;
    cadena Apellido1;
    cadena Apellido2;
    cadena Nom_comp="";
    cout << "Introduzca su nombre: " << endl;
    cin.getline(Nombre,100);
    cout << "Introduzca su primer apellido: " << endl;
    cin.getline(Apellido1,100);
    cout << "Introduzca su segundo apellido: " << endl;
    cin.getline(Apellido2,100);
    strcat(Nom_comp,Nombre);
    strcat(Nom_comp," ");
    strcat(Nom_comp,Apellido1);
    strcat(Nom_comp," ");
    strcat(Nom_comp,Apellido2);
    cout << "Nombre completo: "
         << "\n" << Nom_comp << endl;
    return 0;
}
