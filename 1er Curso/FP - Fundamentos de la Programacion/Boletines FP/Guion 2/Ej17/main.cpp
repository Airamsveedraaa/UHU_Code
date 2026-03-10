#include <iostream>
#include <cmath>
#define k 9e9
using namespace std;

int main()
{
    float q1,q2,r;
    char op;
    cout << "Introduzca sus cargas q1 y q2 y la distancia r entre ellas: " << endl;
    cin >> q1 >> q2 >> r;
    q1=q1*1e-6;
    q2=q2*1e-6;
    float F=k*((q1*q2)/pow(r,2));
    if(F<0)
    {
        cout << "La fuerza de atraccion creada por sus 2 cargas a una distancia r es de:" << F << endl;
        cout << "Desea volver a ejecutar con otros datos diferentes? s/n" << endl;
        cin >> op;
        if(op=='s')
        {
            cout << "Introduzca sus cargas q1 y q2 y la distancia r entre ellas: " << endl;
            cin >> q1 >> q2 >> r;
            q1=q1*1e-6;
            q2=q2*1e-6;
            float F=k*((q1*q2)/pow(r,2));
            if(F<0)
            {
                cout << "La fuerza de atraccion creada por sus 2 cargas a una distancia r es de:" << F << endl;
            }
            else if(F>0)
            {
                cout << "La fuerza de repulsion creada por sus 2 cargas a una distancia r es de:" << F << endl;
            }
        }
        else if(op=='n')
        {
            cout << "Gracias por usar el software" << endl;
        }
    }
    else
    {
        cout << "La fuerza de repulsion creada por sus 2 cargas a una distancia r es de:" << F << endl;
        cout << "Desea volver a ejecutar con otros datos diferentes? s/n" << endl;
        cin >> op;
        if(op=='s')
        {
            cout << "Introduzca sus cargas q1 y q2 y la distancia r entre ellas: " << endl;
            cin >> q1 >> q2 >> r;
            q1=q1*1e-6;
            q2=q2*1e-6;
            float F=k*((q1*q2)/pow(r,2));
            if(F<0)
            {
                cout << "La fuerza de atraccion creada por sus 2 cargas a una distancia r es de:" << F << endl;
            }
            else if(F>0)
            {
                cout << "La fuerza de repulsion creada por sus 2 cargas a una distancia r es de:" << F << endl;
            }
        }
        else if(op=='n')
        {
            cout << "Gracias por usar el software" << endl;
        }
    }
    return 0;
}
