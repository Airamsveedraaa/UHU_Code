#include "Empresa.h"
#include <typeinfo>

Empresa::Empresa():nmaxcli(100)
{
    this->ncli=0;
    this->ncon=0;
    this->contratos=new Contrato*[10];
    this->nmaxcon=10;
}

Empresa::~Empresa()
{
    for(int i=0; i<this->ncon; i++)
    {
        delete this->contratos[i];
    }
    delete [] this->contratos;

    for(int i=0; i<this->ncli; i++)
    {
        delete this->clientes[i];
    }
}

int Empresa::buscarCliente(long int dni)const
{
    int pos=-1;
    int i=0;
    bool existe=false;
    while(i<ncli && !existe)
    {
        if(this->clientes[i]->getDni()==dni)
        {
            pos=i;
            existe=true;
        }
        i++;
    }
    return pos;
}

int Empresa::altaCliente(Cliente *c)
{
    int pos=-1;
    if(this->ncli<nmaxcli)
    {
        this->clientes[this->ncli]=c;
        pos=this->ncli;
        this->ncli++;
    }
    else
    {
        cout << "Lo siento, cupo de clientes lleno" << endl;
        pos=-1;
    }
    return pos;
}

void Empresa::crearContrato()
{
    long int dni;
    cout << "Introduzca dni: ";
    cin >> dni;

    int pos=buscarCliente(dni);

    // Si no existe el cliente, crearlo
    if(pos==-1)
    {
        char nombre[100];
        int dia, mes, anio;

        cout << "Nombre del cliente: ";
        cin.ignore();
        cin.getline(nombre, 100);

        cout << "dia: ";
        cin >> dia;
        cout << "mes: ";
        cin >> mes;
        cout << "anio: ";
        cin >> anio;

        Cliente *c = new Cliente(dni, nombre, Fecha(dia, mes, anio));
        pos = altaCliente(c);
    }

    // Ahora crear el contrato
    int tipo;
    cout << "Tipo de Contrato a abrir (1-Tarifa Plana, 2-Movil): ";
    cin >> tipo;

    int dia, mes, anio;
    cout << "Fecha del contrato" << endl;
    cout << "dia: ";
    cin >> dia;
    cout << "mes: ";
    cin >> mes;
    cout << "anio: ";
    cin >> anio;

    int minutos;
    cout << "minutos hablados: ";
    cin >> minutos;

    // Redimensionar si es necesario
    if(this->ncon == this->nmaxcon)
    {
        nmaxcon *= 2;
        Contrato **nuevo = new Contrato*[nmaxcon];
        for(int i=0; i<ncon; i++)
        {
            nuevo[i] = contratos[i];
        }
        delete [] contratos;
        contratos = nuevo;
    }

    if(tipo == 1) // Tarifa Plana
    {
        this->contratos[ncon++] = new ContratoTP(dni, Fecha(dia, mes, anio), minutos);
    }
    else if(tipo == 2) // Móvil
    {
        float precio;
        char nac[100];

        cout << "Precio minuto: ";
        cin >> precio;
        cout << "Nacionalidad: ";
        cin.ignore();
        cin.getline(nac, 100);

        this->contratos[ncon++] = new ContratoMovil(dni, Fecha(dia, mes, anio), precio, minutos, nac);
    }
}

bool Empresa::cancelarContrato(int idContrato)
{
    bool encontrado = false;
    int i = 0;

    while(i < ncon && !encontrado)
    {
        if(contratos[i]->getIdContrato() == idContrato)
        {
            encontrado = true;
            delete this->contratos[i];

            for(int j=i; j<ncon-1; j++)
            {
                contratos[j] = contratos[j+1];
            }
            ncon--;
        }
        else
        {
            i++;
        }
    }

    // Reducir tamaño si es necesario
    if(ncon > 0 && ncon <= nmaxcon/4 && nmaxcon > 10)
    {
        nmaxcon /= 2;
        Contrato **nuevo = new Contrato*[nmaxcon];
        for(int i=0; i<ncon; i++)
        {
            nuevo[i] = contratos[i];
        }
        delete [] contratos;
        contratos = nuevo;
    }

    return encontrado;
}

bool Empresa::bajaCliente(long int dni)
{
    bool encontrado = false;

    // Primero eliminar todos los contratos del cliente
    int i = 0;
    while(i < ncon)
    {
        if(contratos[i]->getDniContrato() == dni)
        {
            cancelarContrato(contratos[i]->getIdContrato());
            // No incrementar i porque cancelarContrato ya reorganiza el array
        }
        else
        {
            i++;
        }
    }

    // Luego eliminar el cliente
    i = 0;
    while(i < ncli && !encontrado)
    {
        if(clientes[i]->getDni() == dni)
        {
            encontrado = true;
            delete this->clientes[i];

            for(int j=i; j<ncli-1; j++)
            {
                clientes[j] = clientes[j+1];
            }
            ncli--;
        }
        else
        {
            i++;
        }
    }

    return encontrado;
}

int Empresa::nContratosTP() const
{
    int contador = 0;

    for(int i=0; i<ncon; i++)
    {
        if(typeid(*contratos[i]) == typeid(ContratoTP))
        {
            contador++;
        }
    }

    return contador;
}

int Empresa::descuento(float porcentaje) const
{
    int contador = 0;
    float factor = 1.0 - porcentaje/100.0;

    for(int i=0; i<ncon; i++)
    {
        ContratoMovil *cm = dynamic_cast<ContratoMovil*>(contratos[i]);
        if(cm != NULL)
        {
            cm->setPrecioMinuto(cm->getPrecioMinuto() * factor);
            contador++;
        }
    }

    return contador;
}

void Empresa::cargarDatos()
{
    Fecha f1(28, 2, 2001), f2(31, 1, 2002), f3(1, 2, 2002);

    this->clientes[0] = new Cliente(75547001, "Peter Lee", f1);
    this->clientes[1] = new Cliente(45999000, "Juan Perez", Fecha(29, 2, 2000));
    this->clientes[2] = new Cliente(37000017, "Luis Bono", f2);
    this->ncli = 3;

    this->contratos[0] = new ContratoMovil(75547001, f1, 0.12, 110, "DANES");
    this->contratos[1] = new ContratoMovil(75547001, f2, 0.09, 170, "DANES");
    this->contratos[2] = new ContratoTP(37000017, f3, 250);
    this->contratos[3] = new ContratoTP(75547001, f1, 312);
    this->contratos[4] = new ContratoMovil(45999000, f2, 0.10, 202, "ESPAÑOL");
    this->contratos[5] = new ContratoMovil(75547001, f2, 0.15, 80, "DANES");
    this->contratos[6] = new ContratoTP(45999000, f3, 400);
    this->ncon = 7;
}

void Empresa::ver() const
{
    cout << "La Empresa tiene " << ncli << " clientes y " << ncon << " contratos" << endl;
    cout << "Clientes:" << endl;

    for(int i=0; i<ncli; i++)
    {
        cout << "  " << *clientes[i] << endl;
    }

    cout << "Contratos:" << endl;
    for(int i=0; i<ncon; i++)
    {
        cout << "  ";
        contratos[i]->ver();
        cout << endl;
    }
}
