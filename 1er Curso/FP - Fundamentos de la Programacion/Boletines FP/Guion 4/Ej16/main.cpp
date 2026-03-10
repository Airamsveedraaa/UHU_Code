#include <iostream>
#include <cstring>
#include <windows.h>
#define  MAX  5
using namespace std;
typedef char cad[20];

class tprod
{
    cad nombre;   // Nombre del producto
    float precio; // Precio del producto
    int stock;
// Cantidad de producto en el almacén
public:
    tprod();
    void cambiarnombre(cad nom);
    void cambiarprecio(float prec);
    void cambiarstock (int stoc);
    void leenombre (cad nom);
    float leeprecio();
    int leestock();
    bool vender (int cantidad,float &total);
};

class almacen
{
    tprod productos[MAX];
    int nprod;
//Nº de objetos tipo tprod almacenados en productos
public:
    almacen();
    void vaciar();
    int existe(cad nom);

    void verprod (int pos, tprod  &prod);

    int insertar(tprod P);

    void vertabla ();

    bool vender (int pos, int cant, float &total);


};

tprod::tprod()
{

    strcpy(nombre, "NO HAY PRODUCTO");
    precio=0;
    stock=0;

}

void tprod::cambiarnombre(cad nom)
{

    strcpy(nombre,nom);

}

void tprod::cambiarprecio(float prec)
{

    precio=prec;

}

void tprod::cambiarstock(int stoc)
{

    stock=stoc;

}

void tprod::leenombre(cad nom)
{

    strcpy(nom,nombre);

}

float tprod::leeprecio()
{

    return precio;

}

int tprod::leestock()
{

    return stock;

}

bool tprod::vender(int cantidad,float &total)
{

    bool puedes;
    if(cantidad<0 || cantidad>stock)
    {
        puedes=false;
    }

    else
    {
        stock-=cantidad;
        puedes=true;
    }

    return puedes;

}

almacen::almacen()
{

    nprod=0;
}

void almacen::vaciar()
{

    nprod=0;
}

int almacen::existe(cad nom)
{

    int pos=-1;
    int i=0;
    while(i<nprod)
    {
        cad nombre;
        productos[i].leenombre(nombre);
        if(strcmp(nombre,nom)==0)
        {
            pos=i;
        }
        else
            i++;
    }
    return pos;
}

void almacen::verprod(int pos,tprod &prod)
{

    prod=productos[pos];

}

int almacen::insertar(tprod P)
{

    int t;
    if(nprod==MAX){
        t=2;
    }
    cad NombreP;
    P.leenombre(NombreP);

    for(int i=0; i<nprod; i++)
    {
        cad nombreprod;
        productos[i].leenombre(nombreprod);
        if (strcmp(nombreprod,NombreP) == 0)
        {
            t=1;
        }
    }
    productos[nprod]=P;
    nprod++;
    t=0;
    return t;

}

void almacen::vertabla(){
cad nombre;
cout << "INFORMACION DEL ALMACEN: " << endl;
for(int i=0;i<nprod;i++){
    productos[i].leenombre(nombre);
    cout << "NOMBRE PRODUCTO " << i+1 << " : " << nombre
         << "\nSTOCK: " << productos[i].leestock()
         << "\nPRECIO: " << productos[i].leeprecio() << endl;
}

}

bool almacen::vender(int pos,int cant,float &total){
bool puedes;
if(pos>= 0 && pos < nprod)
{
    puedes=productos[pos].vender(cant,total);
}
else
    puedes=false;
return puedes;

}

char menu(){

char opc;
cout << "     MENU     "
     << "\nA.- Visualizar la tabla"
     << "\nB.- Insertar un producto"
     << "\nC.- Vender un producto"
     << "\nD.- Vaciar el almacen"
     << "\nE.- Salir"
     << "\nPon la opcion que deseas: " << endl;
     cin >> opc;
     cin.ignore();
     system("cls");

     return opc;

}
int main()
{

    almacen Mialmacen;
    tprod P1;
    cad nombre;
    char opc;
    int stock;
    float precio;
    int cant;
    float total;
    int pos;
    do{
        opc=menu();
        switch(opc){

    case 'a':
    case 'A':
        Mialmacen.vertabla();
        break;

    case 'b':
    case 'B':
        cout << "Introduzca el nombre del producto: " << endl;
        cin.getline(nombre,20);
        P1.cambiarnombre(nombre);

        cout << "Introduzca stock del producto: " << endl;
        cin >> stock;
        P1.cambiarstock(stock);

        cout << "Introduzca precio del producto: " << endl;
        cin >> precio;
        P1.cambiarprecio(precio);

        Mialmacen.insertar(P1);
        break;

    case 'c':
    case 'C':

        cout << "Introduzca el nombre del producto a vender: " << endl;
        cin.getline(nombre,20);
        cin.ignore();
        pos=Mialmacen.existe(nombre);
        if(pos==-1){
            cout << "No existe el producto" << endl;
        }
        else{
            cout << "Introduzca la cantidad a vender: " << endl;
            cin >> cant;
            total=cant*precio;
            if(Mialmacen.vender(pos,cant,total)){
                cout << "Venta realizada con exito, el total ha sido de: " << total
                     << "\nStock actual: " << P1.leestock() << endl;
            }
            else{
                cout << "No se ha podido realizar la venta" << endl;
            }

            break;

    case 'd':
    case 'D':


        Mialmacen.vaciar();
        cout << "Almacen vaciado" << endl;

        break;

    case 'e':
    case 'E':



        cout << "Saliendo del menu..." << endl;

        break;

    default:
        cout << "Opcion incorrecta" << endl;

        }
        break;
        }
    }while(opc!='e' && opc!= 'E');
    return 0;
}
