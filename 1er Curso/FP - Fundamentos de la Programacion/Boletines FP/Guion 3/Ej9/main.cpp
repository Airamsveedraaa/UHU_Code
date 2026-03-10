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
     i++;
   }
    while(i>j){
        j--;
    }
    if(i>=j){
        cout << "Es palindromo" << endl;
    }
    else
        cout << "No es palindromo" << endl;

    return 0;
}
