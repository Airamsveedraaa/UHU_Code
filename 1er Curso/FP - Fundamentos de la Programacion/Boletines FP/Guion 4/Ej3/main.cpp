#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void rellenar (int T[10][15])
{

    for(int i=0; i<10; i++)
    {

        for(int j=0; j<15; j++)
        {
            T[i][j]=rand()%101;
        }
    }
}

void mostrar (int T[10][15]){


 for(int i=0; i<10; i++)
    {

        for(int j=0; j<15; j++)
        {
            cout << "\t" << T[i][j];
            if(j<15)
                cout << ",";
        }
        cout << endl;
    }

}

bool buscar (int T[10][15],int x){

bool encontrado=false;
int i=0,j;

while(i<10 && !encontrado){
        j=0;
    while(j<15 && !encontrado){
        if(T[i][j]==x)
            encontrado=true;
        else
            j++;
    }
    i++;
}
return encontrado;

}
int main()
{
    srand(time(0));
    int V[10][15];
    rellenar(V);
    mostrar(V);
    int x;
    cout << "Introduzca el numero x a buscar" << endl;
    cin >> x;
    if(buscar(V,x))
        cout << "El numero pertenece a la tabla" << endl;
    else
        cout << "El numero no pertenece a la tabla" << endl;
    return 0;
}
