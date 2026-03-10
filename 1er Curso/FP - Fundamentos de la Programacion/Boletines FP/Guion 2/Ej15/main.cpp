#include <iostream>

using namespace std;

int main()
{
    int a,b;
    cout << "Introduzca sus 2 numeros: " << endl;
    cin >> a >> b;
    do{
    if(a<b){
        b=b-a;
    }
    else if(a>b){
        a=a-b;
    }
    }while(a!=b);
    cout << "Su mcd es " << a << endl;
    return 0;
}
