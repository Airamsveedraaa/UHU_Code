#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int V1[15],V2[15],Vfus[30];
    int N1,N2,opc;
    int total;
    do
    {
        cout << "     MENU     "
             << "\n1.Pedir Vector 1"
             << "\n2.Pedir Vector 2"
             << "\n3.Mostrar Vectores"
             << "\n4.Mezclar Vectores"
             << "\n5.Mostrar Mezcla"
             << "\n6.Salir"
             << "\nElija opcion: " << endl;
        cin >> opc;
        cin.ignore();
        system("cls");

        switch(opc)
        {

        case 1:

            //Pedir Vector 1
            cout << "Cuantos numeros desea añadir al primer vector? " << endl;
            cin >> N1;
            for(int i=0; i<N1; i++)
            {

                cout << "Introduzca el numero " << i+1 << endl;
                cin >> V1[i];
            }

            break;

        case 2:

            //Pedir Vector 2

            cout << "Cuantos numeros desea añadir al segundo vector? " << endl;
            cin >> N2;
            for(int i=0; i<N2; i++)
            {
                cout << "Introduzca el numero " << i+1 << endl;
                cin >> V2[i];
            }

            break;


        case 3:

            cout << "Vector 1: " << endl;
            for(int i=0; i<N1; i++)
            {
                cout << V1[i];
                if(i<N1-1)
                    cout << ",";
                else
                    cout << ".";
            }
            cout << endl;

            cout << "Vector 2: " << endl;
            for(int i=0; i<N2; i++)
            {
                cout << V2[i];
                if(i<N2-1)
                    cout << ",";
                else
                    cout << ".";
            }
            cout << endl;

            break;

        case 4:

            for(int i=0; i<N1; i++)
            {
                Vfus[i]=V1[i];
            }
            for(int i=0; i<N2; i++)
            {
                Vfus[N1+i]=V2[i];
            }
                total=N1+N2;

            for (int i = 0; i < total - 1; i++)
            {
                for (int j = 0; j < total - i - 1; j++)
                {
                    if (Vfus[j] > Vfus[j + 1])
                    {
                        int temp = Vfus[j];
                        Vfus[j] = Vfus[j + 1];
                        Vfus[j + 1] = temp;
                    }
                }
            }
            cout << "Vectores fusionados con exito." << endl;
            break;

        case 5:
            cout << "Vector fusion: " << endl;
            for(int i=0;i<total;i++){
                cout << Vfus[i];
                if(i<total-1)
                    cout << ",";
                else
                    cout << ".";
            }
            cout << endl;
            break;

        case 6:

            cout << "Saliendo del menu..." << endl;
            break;

        default:
            cout << "Error, opcion incorrecta" << endl;
            break;
        }
    }
    while(opc!=6);
    return 0;
}
