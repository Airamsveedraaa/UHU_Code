#include <iostream>
#include <cstring>
using namespace std;
typedef char cadena[30];


void rellenar (cadena D[3][4])
{

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout << "Introduzca la palabra " << i << "," << j << endl;
            cin.getline(D[i][j],30);
        }
    }

}

bool buscar (cadena D[3][4], cadena S, int &f, int &c)
{

    bool encontrado=false;
    int i=0;
    while(i<3 && !encontrado)
    {
        int j=0;
        while(j<4 && !encontrado)
        {
            if(strcmp(S,D[i][j])==0)
            {
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
    char T[3][4][30];
    char S[30];
    rellenar(T);
    int f,c;
    cout << "Introduce la palabra a buscar: " << endl;
    cin.getline(S,30);
    if(buscar(T,S,f,c))
    {
        cout << "La palabra pertenece a la tabla y esta en la posicion " << f << "," << c << endl;
    }
        else
            cout << "La palabra no pertenece a la tabla" << endl;
    return 0;
}
