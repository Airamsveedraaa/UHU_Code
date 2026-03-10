#include <iostream>

using namespace std;

int main()
{
    int N;
    do{
    cout << "Introduzca el orden a calcular de la sucesion de fibonnacci: " << endl;
    cin >> N;
    if(N<1)
        cout << "Error, debe introducir un orden mayor a 1" << endl;
    }while(N<1);
    int a=0,b=1,siguiente;
    for(int i=0;i<N;i++){
        if(i==0){
            cout << a << " " << endl;
        }
        else if(i==1){
            cout << b << " " << endl;
        }
        else{
           siguiente=a+b;
           cout << siguiente << " " << endl;
           a=b;
           b=siguiente;
        }
    }
    return 0;
}
