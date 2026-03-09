#include "Servidor.h"

Servidor::Servidor(cadena dS, cadena nJ,int i, int mxL, int mxC, int p, cadena lG)
{

    strcpy(direccionServidor,dS);
    strcpy(nombreJuego,nJ);
    id=i;
    maxJugadoresConectados=mxL;
    maxJugadoresEnEspera=mxC;
    puerto=p;
    strcpy(localizacionGeografica,lG);
    strcpy(estado,"INACTIVO");
    siguienteServidor=NULL;

}


Servidor::~Servidor()
{



}


int Servidor::getId()
{

    return id;

}


void Servidor::getDireccionServidor(cadena dS)
{

    strcpy(dS,direccionServidor);

}


void Servidor::setSiguienteServidor(Servidor *pS)
{

    siguienteServidor=pS;

}


Servidor* Servidor::getSiguienteServidor()
{

    return siguienteServidor;

}


bool Servidor::conectarJugador(Jugador j)
{

    bool exito=true; //valor a devolver en la funcion

    int longi=jugadoresConectados.longitud();
    int i=1;

    if(longi==maxJugadoresConectados)
    {
        exito=false;
    }
    else
    {
        while(i<=longi && jugadoresConectados.observar(i).puntuacion < j.puntuacion)
        {
            i++;
        }

        jugadoresConectados.insertar(i,j);

    }

    return exito;

}


bool Servidor::ponerJugadorEnEspera(Jugador j)
{

    bool exito=true;
    int longi1=jugadoresEnEspera.longitud(); //Longitud de la cola de jugadores en espera
    int longi2=jugadoresConectados.longitud(); //Longitud de la lista de jugadores conectados

    if(longi2 == maxJugadoresConectados && longi1 < maxJugadoresEnEspera)
    {
        jugadoresEnEspera.encolar(j);
        exito=true;
    }
    else
    {
        exito=false;
    }

    return exito;

}


void Servidor::mostrarJugadoresConectados()
{

    int longi=jugadoresConectados.longitud();

    if(longi==0)
    {
        cout << "No hay jugadores conectados actualmente" << endl;
    }
    else
    {
        cout << "Datos de los jugadores conectados: ";
        for(int i=1; i<=longi; i++)
        {
            cout << "Jugador: " << i
                 << "\nNick: " << jugadoresConectados.observar(i).nombreJugador
                 << "\nID: " << jugadoresConectados.observar(i).ID
                 <<  "\nEstado: " << (jugadoresConectados.observar(i).activo ? "Activo" : "Inactivo")
                 << "\nLatencia: " << jugadoresConectados.observar(i).latencia
                 << "\nPuntuacion: " << jugadoresConectados.observar(i).puntuacion
                 << "\nPais desde el que se ha conectado: " << jugadoresConectados.observar(i).pais << endl;
        }
    }

}


void Servidor::mostrarJugadoresEnEspera()
{

    cola Caux;

    if(jugadoresEnEspera.esvacia())
    {
        cout << "No hay jugadores en espera actualmente" << endl;
    }
    else
    {
        int i=0;
        cout << "Datos de los jugadores en cola de espera : ";
        while(!jugadoresEnEspera.esvacia())
        {
            cout << "Jugador: " << i+1
                 << "\nNick: " << jugadoresEnEspera.primero().nombreJugador
                 << "\nID: " << jugadoresEnEspera.primero().ID
                 << "\nEstado: " << (jugadoresEnEspera.primero().activo ? "Activo" : "Inactivo")
                 << "\nLatencia: " << jugadoresEnEspera.primero().latencia
                 << "\nPuntuacion: " << jugadoresEnEspera.primero().puntuacion
                 << "\nPais desde el que se ha conectado: " << jugadoresEnEspera.primero().pais << endl;
            Caux.encolar(jugadoresEnEspera.primero());
            jugadoresEnEspera.desencolar();
            i++;
        }
        while(!Caux.esvacia())  //restablezco orden original de la cola
        {
            jugadoresEnEspera.encolar(Caux.primero());
            Caux.desencolar();
        }
    }

}


bool Servidor::estaActivo()
{

    return (strcmp(estado,"ACTIVO")==0);

}


bool Servidor::activar()
{

    bool exito=true;

    if(strcmp(estado,"ACTIVO")==0)
    {
        exito=false;
    }

    else if(strcmp(estado,"INACTIVO")==0 || strcmp(estado,"MANTENIMIENTO")==0)
    {
        strcpy(estado,"ACTIVO");
    }
    return exito;
}


bool Servidor::desactivar()
{

    bool exito=true;
    int longi=jugadoresConectados.longitud();

    if(strcmp(estado,"INACTIVO")==0)
    {
        exito=false; //esta inactivo, por lo que no hay que hacer nada
    }

    else if(strcmp(estado,"ACTIVO")==0)
    {

        //esta activo, por lo que se procede a su vaciado para posteriormente ponerlo en inactivo
        //vaciamos lista de jugadores conectados
        for(int i=1; i<=longi; i++)
        {
            jugadoresConectados.eliminar(1);
        }
        //vaciamos cola de jugadores en espera
        while(!jugadoresEnEspera.esvacia())
        {
            jugadoresEnEspera.desencolar();
        }
        strcpy(estado,"INACTIVO"); //ya se ha vaciado, por lo que se pone en inactivo
    }
    else
    {
        strcpy(estado,"INACTIVO"); //caso en el q el servidor este en mantenimiento, por lo que se pone en inactivo directamente
    }
    return exito;

}


bool Servidor::ponerEnMantenimiento()
{

    bool exito=true;

    if(strcmp(estado,"MANTENIMIENTO")==0 || strcmp(estado,"ACTIVO")==0)
    {
        //indica que esta activo o ya en mantenimiento, no se puede poner en mantenimiento
        exito=false;
    }

    else
    {
        strcpy(estado,"MANTENIMIENTO");
    }

    return exito;
}


void Servidor::mostrarInformacion()
{

    //Hallar la latencia media de los jugadores conectados
    int latmedia=0;
    for(int i=1; i<=jugadoresConectados.longitud(); i++)
    {
        latmedia+=jugadoresConectados.observar(i).latencia;
    }

    if(jugadoresConectados.longitud()!=0)
        latmedia=latmedia/jugadoresConectados.longitud();

    cout << "INFORMACION DEL SERVIDOR: "
         << "\nDireccion: " << direccionServidor
         << "\nIdentificador: " << id
         << "\nMaximo de jugadores en linea simultaneos : " << maxJugadoresConectados
         << "\nMaximo de jugadores en espera: " << maxJugadoresEnEspera;
    if(estaActivo())
    {
        cout << "\nNumero real de jugadores en linea simultaneos : " << jugadoresConectados.longitud()
             << "\nJugadores conectados: "<< endl;
        mostrarJugadoresConectados();
        cout << "Numero real de jugadores en espera: " << jugadoresEnEspera.longitud()
             << "\nJugadores en espera de ser conectados: " << endl;
        mostrarJugadoresEnEspera();
    }
    cout << "\nPuerto de escucha: " << puerto
         << "\nLatencia media: " << latmedia
         << "\nUbicacion geografica: " << localizacionGeografica
         << "\nEstado del servidor: " << estado
         << "\n---------------------------------------------------" << endl;

}

bool Servidor::expulsarJugador(cadena nombre)
{

    bool exito=false;
    int i=1;
    cola CAux;
    //primero comprobar que no este en la cola de jugadores en espera el jugador a eliminar
    while(!jugadoresEnEspera.esvacia() && !exito)
    {
        if(strcmp(jugadoresEnEspera.primero().nombreJugador,nombre)==0)
        {
            jugadoresEnEspera.desencolar(); //jugador encontrado en la cola de espera
            exito=true;
        }
        else
        {
            CAux.encolar(jugadoresEnEspera.primero()); //si no se encuentra, se encola en una cola auxiliar para luego devolverlos a la original
            jugadoresEnEspera.desencolar();
        }
    }

    //devolver jugadores no eliminados a la cola de espera
    while(!CAux.esvacia())
    {
        jugadoresEnEspera.encolar(CAux.primero());
        CAux.desencolar();
    }

    //comprobar si el jugador a eliminar esta en la lista de jugadores conectados.
    if(!exito)
    {
        int longi=jugadoresConectados.longitud();
        while(!exito && i<=longi)
        {
            if(strcmp(jugadoresConectados.observar(i).nombreJugador,nombre)==0)
            {
                //jugador encontrado en la lista, procedemos a eliminarlo
                jugadoresConectados.eliminar(i);
                                    //despues de eliminar, comprobar si hay jugadores en espera para ser conectados al servidor
            if(!jugadoresEnEspera.esvacia() && jugadoresConectados.longitud() < maxJugadoresConectados)
            {
                Jugador nuevo=jugadoresEnEspera.primero();
                jugadoresEnEspera.desencolar();
                conectarJugador(nuevo);
                }
                exito=true;
            }
            else
                i++;
        }
    }
    return exito;
}


void Servidor::getNombreJuego(cadena nJ)
{

    strcpy(nJ,nombreJuego);

}


int Servidor::getPuerto()
{

    return puerto;

}


void Servidor::getLocalizacionGeografica(cadena lG)
{

    strcpy(lG,localizacionGeografica);

}


int Servidor::getMaxJugadoresConectados()
{

    return maxJugadoresConectados;

}


int Servidor::getMaxJugadoresEnEspera()
{

    return maxJugadoresEnEspera;

}


int Servidor::getNumJugadoresConectados()
{

    return jugadoresConectados.longitud();

}


int Servidor::getNumJugadoresEnEspera()
{

    return jugadoresEnEspera.longitud();

}


void Servidor::exportarJugadoresConectados(Jugador* conectados)
{

    for(int i=1; i<=jugadoresConectados.longitud(); i++)
    {

        conectados[i-1]=jugadoresConectados.observar(i);
    }

}


void Servidor::exportarJugadoresEnEspera(Jugador* enEspera)
{

    int i=0;
    cola CAux;
    while(!jugadoresEnEspera.esvacia())
    {
        enEspera[i]=jugadoresEnEspera.primero();
        CAux.encolar(jugadoresEnEspera.primero());
        jugadoresEnEspera.desencolar();
        i++;
    }

    while(!CAux.esvacia())
    {
        jugadoresEnEspera.encolar(CAux.primero());
        CAux.desencolar();
    }

}

