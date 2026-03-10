#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int T[10][10],opc;
    int Npar,Nimpar,Ifila,Icol,f1,f2,c1,c2;
    int suma;
    do
    {
        cout << "     MENU     "
             << "\n1.Pedir Datos"
             << "\n2.Mostrar"
             << "\n3.Analizar"
             << "\n4.Sumar una fila"
             << "\n5.Sumar una columna"
             << "\n6.Sumar diagonal principal"
             << "\n7.Sumar diagonal secundaria"
             << "\n8.Intercambiar filas"
             << "\n9.Intercambiar columnas"
             << "\n10.Salir"
             << "\nElija opcion: " << endl;
        cin >> opc;
        cin.ignore();
        system("cls");

        switch(opc)
        {

        case 1:

            for(int i=0; i<10; i++)
            {
                for(int j=0; j<10; j++)
                {
                    do
                    {
                        cout << "Introduzca el numero que ira en la posicion " << i << " " << j << endl;
                        cin >> T[i][j];
                        if(T[i][j]<0)
                        {
                            cout << "Error, el valor debe ser positivo" << endl;
                        }
                    }
                    while(T[i][j]<0);
                }
            }

            break;

        case 2:

            for(int i=0; i<10; i++)
            {
                for(int j=0; j<10; j++)
                {
                    cout << "\t" << T[i][j];
                    if(j<9)
                        cout << ",";
                    else

                    cout << ".";
                }
                cout << endl;
            }
            break;

        case 3:
            Npar,Nimpar=0;
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    if(T[i][j]%2==0)
                        Npar++;
                    else
                        Nimpar++;
                }
            }
            cout << "Recuento: "
                 << "\nTotal pares: " << Npar
                 << "\nTotal nones: " << Nimpar << endl;

                 break;

        case 4:
                suma=0;
            do{
                cout << "Introduzca el indice de la fila a sumar [0-9]" << endl;
                cin >> Ifila;
                if(Ifila<0 || Ifila>9)
                    cout << "Error, el indice debe estar entre 0 y 9" << endl;
                } while(Ifila<0 || Ifila>9);

            for(int i=0;i<10;i++){
                suma+=T[Ifila][i];
            }

            cout << "Resultado de sumar la fila " << Ifila << ": " << suma << endl;

            break;

        case 5:

            suma=0;
            do{
                cout << "Introduzca el indice de la columna a sumar [0-9]" << endl;
                cin >> Icol;
                if(Icol<0 || Icol>9)
                    cout << "Error, el indice debe estar entre 0 y 9" << endl;
                } while(Icol<0 || Icol>9);

            for(int i=0;i<10;i++){
                suma+=T[i][Icol];
            }

            cout << "Resultado de sumar la columna " << Icol << ": " << suma << endl;

            break;

        case 6:

            suma=0;
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                        if(i==j)
                    suma+=T[i][j];
                }
            }
            cout << "Resultado suma diagonal principal: " << suma << endl;

            break;

        case 7:

            suma=0;
            for(int i=0;i<10;i++){
                for(int j=9;j>=0;j--){
                        if(i+j==9)
                    suma+=T[i][j];
                }
            }

            cout << "Resultado suma diagonal secundaria: " << suma << endl;

            break;

        case 8:

            do{
                cout << "Introduzca los indices de las filas a cambiar [0-9] " << endl;
                cin >> f1 >> f2;
                if(f1<0 || f1>9 || f2<0 || f2>9 || f1==f2)
                    cout << "Error, deben estar entre 0 y 9, y NO TENER EL MISMO INDICE" << endl;
            }while(f1<0 || f1>9 || f2<0 || f2>9 || f1==f2);

            for(int i=0;i<10;i++){
                int temp=T[f1][i];
                T[f1][i]=T[f2][i];
                T[f2][i]=temp;
            }

            cout << "Filas intercambiadas con exito" << endl;

            break;

        case 9:
            do{
                cout << "Introduzca los indices de las columnas a cambiar [0-9] " << endl;
                cin >> c1 >> c2;
                if(c1<0 || c1>9 || c2<0 || c2>9 || c1==c2)
                    cout << "Error, deben estar entre 0 y 9, y NO TENER EL MISMO INDICE" << endl;
            }while(c1<0 || c1>9 || c2<0 || c2>9 || c1==c2);

            for(int i=0;i<10;i++){
                int temp=T[i][c1];
                T[i][c1]=T[i][c2];
                T[i][c2]=temp;
            }

            cout << "Columnas intercambiadas con exito" << endl;

            break;

        case 10:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opcion incorrecta" << endl;
            break;
        }
    }
    while(opc!=10);
    return 0;
}
