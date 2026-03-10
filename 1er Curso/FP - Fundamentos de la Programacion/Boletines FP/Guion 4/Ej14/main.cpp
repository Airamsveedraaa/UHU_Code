#include <iostream>
#include <windows.h>
using namespace std;

class Vector
{
    float valores[15];
    int nElem; //Nº de elementos del atributo valores
public:
    Vector();
    bool rellenar (int cuantos);
    void mostrar();
    int getnElem();
    float getValor(int pos);
    int menorRelativo(int P);
    void intercambio (int pos1, int pos2);
};

Vector::Vector()
{

    nElem=0;

}


bool Vector::rellenar(int cuantos)
{

    bool puedes=true;
    if(cuantos<1 || cuantos> 15)
    {
        puedes=false;
    }
    else
    {
        nElem=cuantos;

        for(int i=0; i<nElem; i++)
        {
            cout << "Introduce el numero " << i+1 << endl;
            cin >> valores[i];
        }
    }
    return puedes;

}

void Vector::mostrar()
{

    for(int i=0; i<nElem; i++)
    {
        cout << valores[i];
        if(i<nElem-1)
            cout << ",";
        else
            cout << ".";
    }
    cout << endl;

}

int Vector::getnElem()
{

    return nElem;

}

float Vector::getValor(int pos)
{

    return valores[pos];

}

int Vector::menorRelativo(int P)
{

    float menor=valores[P];
    int indicePos=P;
    for(int i=P; i<nElem; i++)
    {
        if(valores[i]<menor)
        {
            menor=valores[i];
            indicePos=i;
        }
    }
    cout << "El valor mas pequeno es " << menor
         << "\nY se encuentra en la posicion " << indicePos << endl;

    return indicePos;

}

void Vector::intercambio(int pos1, int pos2)
{

    int temp=valores[pos1];
    valores[pos1]=valores[pos2];
    valores[pos2]=temp;

}

int menu()
{

    int opc;

    cout << "     ---MENU---     "
         << "\n1.Insertar datos en vector"
         << "\n2.Mostrar vector"
         << "\n3.Menor relativo"
         << "\n4.Ordenar de menor a mayor"
         << "\n5.Salir"
         << "\nElige opcion: " << endl;
    cin >> opc;
    cin.ignore();
    system("cls");
    return opc;
}

int main()
{
    Vector Vec;
    int N,opc;
    int Pos;
    do
    {
        opc=menu();
        switch(opc)
        {
        case 1:
            cout << "Cuantos numeros desea añadir al vector? " << endl;
            cin >> N;
            if(Vec.rellenar(N))
                cout << "Vector rellenado" << endl;
            else
                cout << "Valor incorrecto, debe estar entre 1 y 15" << endl;

            break;

        case 2:
            if(Vec.getnElem()==0)
            {
                cout << "Vector vacio" << endl;
            }
            else
            {
                cout << "Vector: " << endl;
                Vec.mostrar();
            }

            break;

        case 3:
            do{
            cout << "Desde que posicion quiere buscar? " << endl;
            cin >> Pos;
            if(Pos<1 || Pos>15){
                cout << "Error, debe estar entre 1 y 15" << endl;
                cout << "Introduzca de nuevo la posicion" << endl;
            }
            }while(Pos<1 || Pos>15);

            Vec.menorRelativo(Pos);
            break;

        case 4:
            if(Vec.getnElem()==0){
                cout << "Vector vacio" << endl;
            }

            for(int i=0;i<Vec.getnElem()-1;i++){
                int posMenor=Vec.menorRelativo(i);
                Vec.intercambio(i,posMenor);
            }
            cout << "Vector ordenado" << endl;
            break;

        case 5:
            cout << "Saliendo del menu..." << endl;
            break;

        default:
            cout << "Opcion incorrecta" << endl;
            break;
        }
    }
    while(opc!=5);
    return 0;
}
