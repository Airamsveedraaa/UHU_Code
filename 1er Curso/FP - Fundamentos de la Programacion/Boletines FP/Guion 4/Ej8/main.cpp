#include <iostream>
#include <cstring>
using namespace std;
typedef char cadena [100];

void invertir (char f[250], int ini, int fin){

int longi=strlen(f);
int i=ini-1;
int j=fin-1;
while(i<j){
    char f2=f[i];
    f[i]=f[j];
    f[j]=f2;
    i++;
    j--;
}

}

int main()
{
    cadena f;
    int ini,fin;
    cout << "Introduzca su frase a invertir: " << endl;
    cin.getline(f,100);
    int longi=strlen(f);
    cout << "Desde que caracter de inicio hasta que caracter final desea invertir? " << endl;
    cin >> ini >> fin;
    do{
    if(ini>fin || ini<1 ||fin>longi){
        cout << "No se puede invertir, no se cumplen las condiciones" << endl;
        cout << "Por favor, ingrese de nuevo los valores de inicio y fin: " << endl;
        cin >> ini >> fin;
    }
}while(ini>fin || ini<1 ||fin>longi);

invertir(f,ini,fin);
cout << "Su frase invertida sera: " << f << endl;
    return 0;
}
