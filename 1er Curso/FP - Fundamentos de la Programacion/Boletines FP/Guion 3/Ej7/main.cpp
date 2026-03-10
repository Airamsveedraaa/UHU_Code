#include <iostream>
#include <cstring>
using namespace std;
typedef char cadena [150];
int main()
{
    cadena frase,frase2;
    cout << "Introduzca su frase: " << endl;
    cin.getline(frase,150);
    int longi=strlen(frase);
    int i=0;
   for(int j=0;j<longi;j++)
   {
       if(frase[j]!=' '){
        frase2[i]=frase[j];
        i++;
       }
   }
   strcpy(frase,frase2);
    cout << "Su frase sera: "
         << "\n" << frase << endl;
    return 0;
}
