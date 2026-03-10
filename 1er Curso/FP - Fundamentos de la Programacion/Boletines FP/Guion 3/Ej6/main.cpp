#include <iostream>
#include <cstring>
using namespace std;
typedef char cadena [150];
int main()
{
    cadena frase;
    cout << "Introduzca su frase: " << endl;
    cin.getline(frase,150);
    int i=0;
    while(frase[i]!='\0'){
        if(frase[i]==' '){
            frase[i]='*';
        }
        else
            i++;
    }
    cout << "Su frase sera: "
         << "\n" << frase << endl;
    return 0;
}
