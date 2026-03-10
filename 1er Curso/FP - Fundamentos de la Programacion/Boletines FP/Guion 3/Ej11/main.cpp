#include <iostream>
#include <cstring>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef char cadena [100];
int main()
{
    srand(time(0));
    int opc;
    char VNombres[10][100];
    char VApellidos[10][100];
    do
    {
        cout << "     MENU     "
             << "\n1.Pedir Vector VNombres"
             << "\n2.Pedir Vector VApellidos"
             << "\n3.Mostrar Vectores"
             << "\n4.Generar Nombres de Personas"
             << "\n5.Salir"
             << "\nElija opcion: " << endl;
        cin >>opc;
        cin.ignore();
        system("cls");
        switch(opc)
        {

        case 1:
            //Rellenar vector VNombres
            for(int i=0; i<10; i++)
            {
                cout << "Introduzca el nombre de la persona " << i+1 << endl;
                cin.getline(VNombres[i],100);
            }
            break;

        case 2:
            for(int i=0; i<10; i++)
            {
                cout << "Introduzca el nombre de la persona " << i+1 << endl;
                cin.getline(VApellidos[i],100);
            }

            break;

        case 3:
            for(int i=0; i<10; i++)
            {
                cout << VNombres[i];
                if(i<9)
                {
                    cout << ",";
                }
            }
            cout << endl;

            for(int i=0; i<10; i++)
            {
                cout << VApellidos[i];
                if(i<9)
                {
                    cout << ",";
                }
            }
            cout << endl;

            break;

        case 4:
            int N;
            cout << "Cuantos nombres desea generar: " << endl;
            cin >> N;
            cin.ignore();
            for(int i=0; i<N; i++)
            {
                int indiceNombre=rand()%10;
                int indiceAPellido=rand()%10;
                cout << VNombres[indiceNombre] << ", " << VApellidos[indiceAPellido] << endl;
            }
            break;

        case 5:
            cout << "Saliendo del menu..." << endl;
            break;

        default:
            cout << "Error, opcion incorrecta" << endl;
            break;
        }
    }
    while(opc!=5);
    return 0;
}
