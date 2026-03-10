#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int opc;
    int V1[10],V2[10];
    do
    {

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
        switch(opc)
        {

        case 1:
            //Pedir Vector 1
            for(int i=0; i<10; i++)
            {
                cout << "Introduzca el valor " << i+1 << " del Vector 1" << endl;
                cin >> V1[i];
            }
            break;

        case 2:

            //Pedir Vector 2

            for(int i=0; i<10; i++)
            {
                cout << "Introduzca el valor " << i+1 << " del Vector 2" << endl;
                cin >> V2[i];
            }

            break;

        case 3:

            //Mostrar Vector 1

            cout << "Vector 1: ";

            for(int i=0; i<10; i++)
            {
                cout << V1[i];
                if(i<9)
                    cout << ",";
                else
                    cout << ".";
            }
            cout << endl;

            //Mostrar Vector 2

            cout << "Vector 2: ";

            for(int i=0; i<10; i++)
            {
                cout << V2[i];
                if(i<9)
                    cout << ",";
                else
                    cout << ".";
            }
            cout << endl;

            break;

        case 4:
            {

            //Comprobar valores
            int i=0;
            bool iguales=true;
          while(i<10 && iguales){
            if(V1[i]!=V2[i]){
                iguales=false;
            }
            else
                i++;
          }

          if(iguales){
            cout << "Son iguales" << endl;
          }
          else
            cout << "No son iguales" << endl;
            break;
            }

        case 5:

            cout << "Saliendo del menu..." << endl;
            break;

        default:
            cout << "Opcion incorrecta" << endl;
            break;
        }
    }
    while(opc!=5);
    return 0;
}
