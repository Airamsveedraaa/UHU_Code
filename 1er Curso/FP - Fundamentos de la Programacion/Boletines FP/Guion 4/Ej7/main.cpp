#include <iostream>
#include <cstring>
using namespace std;
typedef char cadena[250];

void compactar (char f[250], char c){

cadena f1,f2;
strcpy(f1,f);
int longi=strlen(f);
int i=0;
   for(int j=0;j<longi;j++)
   {
       if(f1[j]!=c){
        f2[i]=f1[j];
        i++;
       }
   }
   strcpy(f,f2);
}
int main()
{
    cadena frase;
    char c;
    cout << "Introduzca su frase a compactar: " << endl;
    cin.getline(frase,250);
    cout << "Que caracter desea eliminar de la frase? " << endl;
    cin >> c;
    compactar(frase,c);
    cout << "Su frase sera: " << frase << endl;
    return 0;
}
