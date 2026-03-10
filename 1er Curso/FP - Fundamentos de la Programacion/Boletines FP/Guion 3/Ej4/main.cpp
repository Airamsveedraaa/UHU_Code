#include <iostream>
#include <cstring>
using namespace std;

typedef char cadena[30];

int main()
{
    char diccionario[3][4][30];
    char S[30];
    bool encontrado=false;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout << "Introduzca la palabra de la posicion " << i+1 << j+1 << endl;
            cin.getline(diccionario[i][j],30);
        }
    }
    cout << "Introduzca la palabra S a buscar: " << endl;
    cin.getline(S,30);
    int i=0;
    while(i<3 && !encontrado)
    {
        int j=0;
        while(j<4 && !encontrado)
        {
            if(strcmp(S,diccionario[i][j])==0)
            {
                encontrado=true;
            }
            else
                j++;
        }
        i++;
    }
    if(encontrado)
        cout << "Su palabra S pertenece a la tabla" << endl;
    else
        cout << "Su palabra S no pertenece a la tabla" << endl;
    return 0;
}
