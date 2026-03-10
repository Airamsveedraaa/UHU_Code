#include <iostream>
#include <windows.h>
using namespace std;

int menu(){
int opc;

     cout << "     MENU     "
             << "\n1.Pedir Vector 1"
             << "\n2.Pedir Vector 2"
             << "\n3.Mostrar Vectores"
             << "\n4.Comprobar Vectores"
             << "\n5.Salir"
             << "\nElija opcion: " << endl;
        cin >>opc;
        cin.ignore();
        system("cls");
return opc;

}
void rellenar (int v[10]){

for(int i=0;i<10;i++){
    cout << "Introduzca el numero " << i+1 << " del vector: " << endl;
    cin >> v[i];
}

}

void mostrar (int v[10]){

for(int i=0;i<10;i++){
    cout << v[i];
    if(i<9)
        cout << ",";
    else
        cout << ".";
}
cout << endl;
}

bool iguales(int v1[10],int v2[10]){

bool encontrado=true;
int i=0;
while(i<10 && encontrado){
        if(v1[i]!=v2[i])
            encontrado=false;
        else
             i++;
    }

return encontrado;
}

int main()
{
    int vec1[10],vec2[10];
    int opcion;
    do{
        opcion=menu();
        switch(opcion){

    case 1:
        rellenar(vec1);
        cout << "Vector 1 rellenado" << endl;
        break;

    case 2:
        rellenar(vec2);
        cout << "Vector 2 rellenado" << endl;
        break;

    case 3:
        cout << "Vector 1:" << endl;
        mostrar(vec1);
        cout << "Vector 2:" << endl;
        mostrar(vec2);
        break;

    case 4:
        if(iguales(vec1,vec2)){
            cout << "Son iguales"  << endl;

        }
        else
            cout << "No son iguales" << endl;
        break;

    case 5:
        cout << "Saliendo del menu..." << endl;
        break;

    default:
        cout << "Opcion incorrecta" << endl;

        }
    }while(opcion!=5);
    return 0;
}
