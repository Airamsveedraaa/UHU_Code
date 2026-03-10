#include <iostream>

using namespace std;

int main()
{
    int T1,T2;
    do{
        cout << "Introduzca la primera y ultima tabla a calcular: " << endl;
        cin >> T1 >> T2;
        if(T1<1 || T1>10 || T2<1 || T2>10)
            cout << "Ambos indices deben estar entre 0 y 10" << endl;
    } while(T1<1 || T1>10 || T2<1 || T2>10);
    if(T1>T2){
        int temp=T1;
        T1=T2;
        T2=temp;
    }
    for(int i=1;i<=10;i++){
        for(int j=T1;j<=T2;j++){
            cout << j << "x" << i << "=" << i*j << "\t";
        }
        cout << endl;
    }
    return 0;
}
