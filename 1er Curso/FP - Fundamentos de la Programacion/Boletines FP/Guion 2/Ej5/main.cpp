#include <iostream>

using namespace std;

int main()
{
    int N;
    cout << "Introduzca el año: " << endl;
    cin >> N;
    if(N%400==0 || N%4==0 && N%100!=0)
        cout << "Su año es bisiesto" << endl;
    else
        cout << "Su año no es bisiesto" << endl;
    return 0;
}
