#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));
    int T[10][15];
    int X;
    bool encontrado=false;
    //Sistema de recorrido para rellenar tabla
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<15; j++)
        {
            T[i][j]=rand()%101;
        }
    }
    //Sistema de busqueda
    cout << "Introduzca su valor X a buscar: " << endl;
    cin >> X;

    int i=0;
    while(i<10 && !encontrado)
    {
        int j=0;
        while(j<15 && !encontrado)
        {
            if(T[i][j]==X)
                encontrado=true;
            else
                j++;
        }
        i++;
    }
    if(encontrado)
        cout << "Su numero X pertenece a la tabla" << endl;
    else
        cout << "Su numero X no pertenece a la tabla" << endl;
    return 0;
}
