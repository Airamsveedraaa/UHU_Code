#include <iostream>
#include <cstring>
using namespace std;
typedef char cadena [250];

bool palindroma (char f[250]){

bool espalindromo=true;
 int longi=strlen(f);
    int j=longi-1;
    int i=0;
    while(i<j)
   {
     if(f[i]!=f[j]){
        espalindromo=false;
     }
     else
    i++;
     j--;

       return espalindromo;
}
}

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
    cadena f;
    char c;
    cout << "Introduzca su frase a comprobar: " << endl;
    cin.getline(f,250);
    //Eliminamos espacios
    c=' ';
    compactar(f,c);
    if(palindroma(f))
        cout << "es palindromo" << endl;
    else
        cout << "No es palindromo" << endl;
    return 0;
}
