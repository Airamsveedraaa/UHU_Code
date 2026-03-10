#include <iostream>
#include <cstring>
using namespace std;

typedef char cadena [100];
int main()
{
    cadena frase;
    cout << "Introduzca una frase: " << endl;
    cin.getline(frase,100);
    int longi=strlen(frase);
    int j=longi-1;
    int i=0;
    while(i<j)
    {
    char frase2=frase[i];
    frase[i]=frase[j];
    frase[j]=frase2;
    i++;
    j--;
    }
    cout << "Su frase invertida es: "
         << "\n" << frase << endl;
    return 0;
}
