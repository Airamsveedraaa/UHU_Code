#include "GestorServidores.h"
#include "Servidor.h"

GestorServidores::GestorServidores()
{

    primerServidor=NULL; //inicializo al primer puntero �?

    numServidores=0; //al inicio 0 elementos efectivos

}

GestorServidores::~GestorServidores()
{

    Servidor* servidorActual= primerServidor;

    while(servidorActual!=NULL)
    {
        Servidor* siguiente=servidorActual->getSiguienteServidor();
        delete servidorActual;
        servidorActual=siguiente;
    }
    primerServidor=NULL;
    numServidores=0;

}


int GestorServidores::getNumServidores()
{

    return numServidores;

}


bool GestorServidores::desplegarServidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG)
{

//creamos objeto y variable booleana
    bool exito=true;

    Servidor* ServidorActual=new Servidor(dS,nJ,i,mxL,mxC,p,lG); //Servidor a desplegar

    if(ServidorActual==NULL)
    {
        cout << "No hay espacio para desplegar el nuevo servidor" << endl;
        exito=false; //no hay memoria para a�adir el servidor
    }

    else
    {
        //comprobaciones
        Servidor* Actual=primerServidor; //Servidor auxiliar para movernos entre nodos
        cadena dirr;
        while(Actual!=NULL)
        {
            Actual->getDireccionServidor(dirr);
            if(Actual->getId()==i)
            {
                cout << "Ya existe un servidor con esa ID" << endl;
                exito=false; //mismo id
            }
            else if(strcmp(dS,dirr)==0)
            {
                cout << "Ya existe un servidor con esa direccion" << endl;
                exito=false; //mismo nombre de juego
            }

            Actual=Actual->getSiguienteServidor();
        }
        if(exito)
        {
            //quiere decir que podemos desplegar

            //caso 1, al inicio de la lista
            if(primerServidor==NULL)
            {
                ServidorActual->setSiguienteServidor(primerServidor);
                primerServidor=ServidorActual;

            }
            else
            {
                cadena p;
                primerServidor->getLocalizacionGeografica(p);
                if(strcmp(p,lG)<0)
                {
                    ServidorActual->setSiguienteServidor(primerServidor);
                    primerServidor=ServidorActual;
                }
                else
                {
                    Servidor* anterior=primerServidor;
                    Servidor* actual=primerServidor->getSiguienteServidor();
                    bool SvInsertado=false;
                    while(actual!=NULL && !SvInsertado)
                    {
                        cadena localA;
                        actual->getLocalizacionGeografica(localA);
                        if(strcmp(localA,lG)<0)
                        {
                            ServidorActual->setSiguienteServidor(actual);
                            anterior->setSiguienteServidor(ServidorActual);
                            actual=NULL;
                            SvInsertado=true;
                        }
                        else
                        {
                            anterior=actual;
                            actual=actual->getSiguienteServidor();
                        }
                    }
                    if(!SvInsertado)
                    {
                        anterior->setSiguienteServidor(ServidorActual);
                        ServidorActual->setSiguienteServidor(NULL);
                    }
                }
            }
            numServidores++;
        }

    }

    return exito;
}


bool GestorServidores::desconetarServidor(cadena dS)
{

    bool exito=false;
    bool encontrado=false;
    Servidor* Aux=primerServidor;

    while(Aux!=NULL && !encontrado)
    {
        cadena dir;
        Aux->getDireccionServidor(dir);
        if(strcmp(dir,dS)==0)
        {
            //servidor encontrado
            encontrado=true;
            cadena nomj;
            Aux->getNombreJuego(nomj);

            int Max=Aux->getMaxJugadoresConectados();
            Jugador *conectados=new Jugador[Aux->getMaxJugadoresConectados()];
            Aux->exportarJugadoresConectados(conectados);
            exito = Aux->desactivar();

            //ordenar vector para distribucion ya ordenada
            for(int i=0; i<Max; i++)
            {
                for(int j=i+1; j<Max; j++)
                {
                    if(conectados[i].latencia > conectados[j].latencia)
                    {
                        Jugador temp=conectados[i];
                        conectados[i]=conectados[j];
                        conectados[j]=temp;
                    }
                }
            }
            //Distribucion de jugadores
            for(int i=0; i<Max; i++)
            {
                cadena host;
                bool enEspera;
                alojarJugador(conectados[i],nomj,host,enEspera);
            }
            delete [] conectados;
        }
        else
        {
            Aux=Aux->getSiguienteServidor();
        }
    }

    return exito;
}


bool GestorServidores::conectarServidor(cadena dS)
{

    bool exito=false;
    if(primerServidor==NULL)
    {
        exito=false; //error, no hay servidores
    }

    else
    {
        //buscar servidor coincidente para activarlo
        Servidor* ServerAux=primerServidor; //Servidor auxiliar para recorrer y encontrar posicion en donde activar
        while(ServerAux!=NULL)
        {
            cadena dir;
            ServerAux->getDireccionServidor(dir);
            if(strcmp(dir,dS)==0)
            {
                //Posicion encontrada, activamos server
                ServerAux->activar();
                exito=true;
            }
            ServerAux=ServerAux->getSiguienteServidor();
        }
    }

    return exito;
}


bool GestorServidores::realizarMantenimiento(cadena dS)
{

    bool exito;
    if(primerServidor==NULL)
    {
        exito=false; //error, no hay servidores
    }

    else
    {
        //buscar servidor coincidente para activarlo
        Servidor* ServerAux=primerServidor; //Servidor auxiliar para recorrer y encontrar posicion en donde realizar mantenimiento
        while(ServerAux!=NULL)
        {
            cadena dir;
            ServerAux->getDireccionServidor(dir);
            if(strcmp(dir,dS)==0)
            {
                //Posicion encontrada, ponemos en mantenimiento el server
                exito=ServerAux->ponerEnMantenimiento();
            }
            ServerAux=ServerAux->getSiguienteServidor();
        }
    }

    return exito;
}


bool GestorServidores::eliminarServidor(cadena dS)
{
    bool exito=false;

    if(primerServidor==NULL)
    {
        exito=false; //no hay servidores
    }
    else
    {
        //probar si es el primer servidor
        cadena dir;
        primerServidor->getDireccionServidor(dir);
        if(strcmp(dir,dS)==0 && !primerServidor->estaActivo())
        {
            Servidor* Borr=primerServidor;
            primerServidor=primerServidor->getSiguienteServidor();
            delete Borr;
            numServidores--;
            exito=true;
        }

        else
        {
            //comprobar cual es el que hay que eliminar, pues no es el primero
            Servidor* ServerAux=primerServidor->getSiguienteServidor(); //Servidor auxiliar para moverme, se usa despues de ver que no es el primer servidor
            Servidor* Ant=primerServidor;
            while(ServerAux!=NULL)
            {
                ServerAux->getDireccionServidor(dir);
                if(strcmp(dir,dS)==0 && !ServerAux->estaActivo())
                {
                    Ant->setSiguienteServidor(ServerAux->getSiguienteServidor());
                    delete ServerAux;
                    numServidores--;
                    exito=true;
                }
                Ant=ServerAux;
                ServerAux=ServerAux->getSiguienteServidor();
            }
        }

    }
    return exito;
}


bool GestorServidores::alojarJugador(Jugador j, cadena nomJuego, cadena host, bool &enEspera)
{
    bool Alojado=false;
    Servidor* Aux=primerServidor;
    Servidor* MejorServidorConexion=NULL;
    int MaxEspacioConexion=-1; //variable para almacenar el vector con mayor diferencia entre jugadores alojados y jugadores maximos

    //Primero encontrar servidor con mayor espacio en la lista de conectados
    while(Aux!=NULL)
    {
        cadena nomj;
        Aux->getNombreJuego(nomj);
        if(Aux->estaActivo() && strcmp(nomj,nomJuego)==0)
        {
            int espacio= Aux->getMaxJugadoresConectados() - Aux->getNumJugadoresConectados();
            if(espacio > MaxEspacioConexion)
            {
                MaxEspacioConexion=espacio;
                MejorServidorConexion=Aux;
            }
        }
        Aux=Aux->getSiguienteServidor();
    }

    if(MejorServidorConexion!=NULL && MejorServidorConexion->conectarJugador(j))
    {
        //Si se cumple quiere decir que tengo espacio y el server esta activo correctamente
        //Alojo jugador
        MejorServidorConexion->getDireccionServidor(host);
        Alojado=true;
        enEspera=false;
    }
    else
    {
        //Si no lo aloja en el anterior, quiere decir que no hay espacio, buscamos el que mas hueco tenga en espera
        Servidor* MejorServidorEspera=NULL;
        int MaxEspacioEspera=-1;
        Aux=primerServidor;

        while(Aux!=NULL)
        {
            cadena nomj;
            Aux->getNombreJuego(nomj);
            if( Aux->estaActivo() && strcmp(nomj,nomJuego)==0)
            {
                int espacio= Aux->getMaxJugadoresEnEspera() - Aux->getNumJugadoresEnEspera();
                if(espacio > MaxEspacioEspera)
                {
                    MaxEspacioEspera=espacio;
                    MejorServidorEspera=Aux;
                }
            }
            Aux=Aux->getSiguienteServidor();
        }

        if(MejorServidorEspera!=NULL && MejorServidorEspera->ponerJugadorEnEspera(j))
        {
            MejorServidorEspera->getDireccionServidor(host);
            Alojado=false;
            enEspera=true;
        }
        else
        {
            Alojado=false;
            enEspera=false;
        }
    }

    return Alojado;
}

bool GestorServidores::expulsarJugador(cadena nJ, cadena host)
{

    bool exito=false;

    Servidor* Aux=primerServidor;

    while(!exito && Aux!=NULL)
    {
        //obtenemos direccion de cada servidor para comprobar si el jugador a eliminar esta en la lista o cola del que comprobemos en cada instante
        if(Aux->expulsarJugador(nJ))
        {
            Aux->getDireccionServidor(host);
            exito=true;
        }

        Aux=Aux->getSiguienteServidor();
    }
    return exito;
}

int GestorServidores::getPosicionServidor(cadena dS)
{
    int Pos=-1; //valor a devolver, -1 por defecto
    int p=1;    //valor para recorrer e ir actualizando

    Servidor* Aux=primerServidor;

    while(Aux!=NULL)
    {
        cadena aux;
        Aux->getDireccionServidor(aux);
        if(strcmp(aux,dS)==0)
        {
            Pos=p;
        }
        Aux=Aux->getSiguienteServidor();
        p++;
    }
    return Pos;
}


void GestorServidores::mostrarInformacionServidores(int pos)
{

    if(pos==-1)
    {
        if(primerServidor==NULL){

            cout << "No hay servidores desplegados" << endl;
        }
        else{
        Servidor* Aux=primerServidor;
        int cont=1;
        while(Aux!=NULL)
        {
            cout << "Servidor : " << cont << " ";
            Aux->mostrarInformacion();
            cout << endl;
            Aux=Aux->getSiguienteServidor();
            cont++;
        }

    }
    }
    else if (pos < 1 || pos > numServidores)
    {
         cout << "Posicion fuera de rango" << endl;
    }
    else
    {

        Servidor* Aux=primerServidor;
        for(int i=1; i<pos; i++)
        {
            Aux=Aux->getSiguienteServidor();
        }
        Aux->mostrarInformacion();
    }

}

bool GestorServidores::jugadorConectado(cadena nJ,cadena dS)
{

    bool exito=false;
    bool PerteneceJ=false;
//primero, encontrar el servidor con dicha cadena �?
    Servidor* Aux=primerServidor;
    while(Aux!=NULL && !exito)
    {
        cadena aux;
        Aux->getDireccionServidor(aux);
        if(strcmp(aux,dS)==0)
        {
            //Servidor encontrado, exportamos los jugadores a un vector auxiliar para recorrer comparando
            int max=Aux->getMaxJugadoresConectados();
            Jugador* conectados=new Jugador[max];
            Aux->exportarJugadoresConectados(conectados);
            int i=0;
            while(!PerteneceJ && i<max)
            {
                if(strcmp(conectados[i].nombreJugador,nJ)==0)
                {
                    PerteneceJ=true;
                }
                i++;
            }
            delete [] conectados;
        }
        Aux=Aux->getSiguienteServidor();
    }

    if(PerteneceJ)
    {
        exito=true;
    }
    return exito;
}

bool GestorServidores::jugadorEnEspera(cadena nJ, cadena dS)
{

    bool exito=false;
    bool PerteneceJ=false;
    Servidor* Aux=primerServidor;
    while(Aux!=NULL && !exito)
    {
        cadena aux;
        Aux->getDireccionServidor(aux);
        if(strcmp(aux,dS)==0)
        {
            //Servidor encontrado, exportamos cola
            int max=Aux->getMaxJugadoresEnEspera();
            Jugador* enCola=new Jugador[max];
            Aux->exportarJugadoresEnEspera(enCola);
            int i=0;
            while(!PerteneceJ && i<max)
            {
                if(strcmp(enCola[i].nombreJugador,nJ)==0)
                {
                    PerteneceJ=true;
                }
                i++;
            }
            delete [] enCola;
        }
        Aux=Aux->getSiguienteServidor();
    }
    if(PerteneceJ)
    {
        exito=true;
    }
    return exito;

}

bool GestorServidores::jugadorConectado(cadena nJ)
{

    bool exito=false;
    bool PerteneceJ=false;
    Servidor* Aux=primerServidor;
    while(Aux!=NULL && !exito)
    {
        cadena direcc;
        Aux->getDireccionServidor(direcc);
        if(jugadorConectado(nJ,direcc))
        {
            PerteneceJ=true;
        }
        Aux=Aux->getSiguienteServidor();
    }
    if(PerteneceJ)
    {
        exito=true;
    }

    return exito;
}


bool GestorServidores::jugadorEnEspera(cadena nJ)
{

    bool exito=false;
    Servidor* Aux=primerServidor;
    while(Aux!=NULL && !exito)
    {
        cadena direcc;
        Aux->getDireccionServidor(direcc);
        if(jugadorEnEspera(nJ,direcc))
        {
            exito=true;
        }
        else
            Aux=Aux->getSiguienteServidor();
    }

    return exito;


}

