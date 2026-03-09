#include "GestorServidores.h"

//(incluir ambas funciones en main.cpp.
Jugador creaJugador(cadena n, int id, bool c, int l, long p, cadena pa)
{
    Jugador r;
    strcpy(r.nombreJugador, n);
    r.ID = id;
    r.activo = c;
    r.latencia = l;
    r.puntuacion = p;
    strcpy(r.pais, pa);

    return r;
}

//invocar esta funci�n desde main pasando como argumento el objeto de la
//clase GestorServidores utilizado en la misma, justo despu�s de su declaraci�n.
void inicializarDatosPruebas(GestorServidores &gS)
{
    //modificar para crear los jugadores/servidores a conveniencia.
    Jugador j1 = creaJugador("Jan27", 23002, false, 25, 23000, "Italia");
    Jugador j2 = creaJugador("Rocio_Roma", 34011, false, 32, 27000, "Francia");
    Jugador j3 = creaJugador("LuisG", 33007, false, 15, 21000, "Reino Unido");
    Jugador j4 = creaJugador("Maria005", 45055, false, 28, 24400, "Francia");
    Jugador j5 = creaJugador("PacoRomero", 35054, false, 18, 14445, "Espa�a");
    Jugador j6 = creaJugador("Carmen56", 35062, false, 42, 12305, "Estonia");
    Jugador j7 = creaJugador("LouisX_23", 25022, false, 65, 45405, "Estonia");
    Jugador j8 = creaJugador("O-O_Yep", 33121, false, 12, 11345, "Italia");
    Jugador j9 = creaJugador("PacoPePe", 22012, false, 32, 23422, "Espa�a");
    Jugador j10 = creaJugador("Wilson2001", 21252, false, 23, 4345, "Reino Unido");

    gS.desplegarServidor("175.23.34.66", "DemonSlayer 2", 320002, 2, 3, 4, "Moldavia");
    gS.conectarServidor("175.23.34.66");
    gS.desplegarServidor("systemrs.server0092.fr", "DemonSlayer 2", 320004, 2, 2, 6, "Francia");
    gS.conectarServidor("systemrs.server0092.fr");
    gS.desplegarServidor("systemrs.server0042.es", "Quake Heroes", 320082, 2, 2, 6, "Espa�a");
    gS.conectarServidor("systemrs.server0042.es");

    cadena h;

    bool es;

    gS.alojarJugador(j1, "DemonSlayer 2", h, es);
    gS.alojarJugador(j2, "DemonSlayer 2", h, es);
    gS.alojarJugador(j3, "DemonSlayer 2", h, es);
    gS.alojarJugador(j4, "DemonSlayer 2", h, es);
    gS.alojarJugador(j5, "DemonSlayer 2", h, es);
    gS.alojarJugador(j6, "DemonSlayer 2", h, es);
    gS.alojarJugador(j7, "Quake Heroes", h, es);
    gS.alojarJugador(j8, "Quake Heroes", h, es);
    gS.alojarJugador(j9, "Quake Heroes", h, es);
    gS.alojarJugador(j10, "Quake Heroes", h, es);
}

int menu()
{
    int opcion;
    do
    {
        CLS;
        cout<<"GESTOR DE SERVIDORES   v1.0"<<endl;
        cout<<"================================"<<endl;
        cout<<"1. Mostrar Servidor\n2. Crear Servidor\n3. Eliminar servidor\n4. ActivarServidor"<<endl;
        cout<<"5. Desactivar Servidor\n6. Programar mantenimiento de servidor\n7. Conectar jugador"<<endl;
        cout<<"8. Expulsar jugador\n9. Salir\n"<<endl;
        cout<<"Indique la opcion deseada: ";
        cin>>opcion;
        cin.ignore();
        if(opcion<1 || opcion>9)
        {
            cout<<"Opcion no valida, intentelo de nuevo\n\n";
            PAUSE;
        }
    }
    while(opcion<1 || opcion>9);

    return opcion;
}

int main()
{

    srand(time(0));
    int opc;
    GestorServidores Gestor;
    inicializarDatosPruebas(Gestor);
    do
    {
        opc = menu();

        switch(opc)
        {

        case 1:
        {
            cadena direccion;
            cout << "Introduzca la direccion/hostname del servidor a mostrar (ALL para mostrar todos): " << endl;
            cin.getline(direccion,50);

            if(strcmp(direccion, "ALL") == 0)
            {
                if(Gestor.getNumServidores() > 0)
                {
                    Gestor.mostrarInformacionServidores(-1);
                }
                else
                {
                    cout << "No hay servidores para mostrar" << endl;
                }
            }
            else
            {
                int pos = Gestor.getPosicionServidor(direccion);

                if(pos == -1)
                {
                    cout << "No existe ningun servidor con esa direccion/hostname " << endl;
                }
                else
                {
                    Gestor.mostrarInformacionServidores(pos);
                }
            }
        }
        break;

        case 2:
        {
            cadena direccion;
            cadena nombreJuego;
            cadena Pais;
            int ID,MaxConectados,MaxEnEspera,Puerto;

            cout << "Introduzca los datos del servidor a desplegar: " << endl;
            cout << "Direccion/hostname: ";
            cin.getline(direccion,50);
            cout << "Nombre del juego que aloja el servidor: ";
            cin.getline(nombreJuego,50);
            cout << "ID: ";
            cin >> ID;
            cout << "Maximo de jugadores que podran conectarse: ";
            cin >> MaxConectados;
            cout << "Maximo de jugadores que podran estar en espera de conectarse: ";
            cin >> MaxEnEspera;
            cout << "Puerto de escucha: ";
            cin >> Puerto;
            cin.ignore();
            cout << "Pais donde estara alojado el servidor: ";
            cin.getline(Pais,50);

            Gestor.desplegarServidor(direccion,nombreJuego,ID,MaxConectados,MaxEnEspera,Puerto,Pais);

        }
        break;

        case 3:
        {
            cadena direccion;
            cout << "Introduzca la direccion/hostname del servidor a eliminar: " << endl;
            cin.getline(direccion,50);

            bool eliminado=Gestor.eliminarServidor(direccion);
            if(eliminado==false)
            {
                cout << "Servidor a eliminar no existente" << endl;
            }
            else
            {
                cout << "Servidor eliminado con exito" << endl;
            }

        }
        break;

        case 4:
        {

            cadena direccion;
            cout << "Introduzca la direccion/hostname del servidor a activar: " << endl;
            cin.getline(direccion,50);
            bool activado=Gestor.conectarServidor(direccion);
            if(activado==false)
            {
                cout << "Servidor ya activo" << endl;
            }
            else
                cout << "Servidor activado con exito" << endl;

        }
        break;

        case 5:
        {
            cadena direccion;
            cout << "Introduzca la direcciion/hostname del servidor a desactivar: " << endl;
            cin.getline(direccion,50);

            bool desactivado=Gestor.desconetarServidor(direccion);

            if(!desactivado)
            {
                cout << "Servidor a desactivar no existente" << endl;
            }
            else
                cout << "Servidor desactivado con exito" << endl;

        }
        break;

        case 6:
        {

            cadena direccion;
            cout << "Introduzca la direccion hostname del servidor a poner en mantenimiento: " << endl;
            cin.getline(direccion,50);

            bool mantenimiento=Gestor.realizarMantenimiento(direccion);

            if(mantenimiento)
            {
                cout << "Mantenimiento programado con exito" << endl;
            }
            else
            {
                cout << "El servidor a poner en mantenimiento esta activo o ya en mantenimiento, desactivelo primero" << endl;

            }

        }
        break;

        case 7:
        {
            Jugador j;
            cadena nombreJugador;
            cout << "Introduzca el nick del jugador a conectar: " << endl;
            cin.getline(j.nombreJugador,50);

            if(Gestor.jugadorConectado(nombreJugador))
            {
                cout << "Error, el jugador con nick " << nombreJugador << " ya se encuentra conectado al sistema" << endl;
            }

            else
            {
                cadena nombreJuego;
                bool activo=true;
                cout << "El jugador no se encuentra conectado al sistema actualmente, introduzca los datos del jugador a conectar: ";
                cout << "ID: " << endl;
                cin >> j.ID;
                cin.ignore();
                cout << "Pais desde el que se conecta al sistema: " << endl;
                cin.getline(j.pais,50);
                cout << "Nombre del juego que va a jugar: " << endl;
                cin.getline(nombreJuego,50);
                j.latencia = 1 + rand() % 500;
                j.puntuacion= rand() % 100000;
                j.activo=true;
                //intentar conectar al jugador

                cadena host;
                bool enEspera;
                bool conectado=Gestor.alojarJugador(j,nombreJuego,host,enEspera);
                if(conectado)
                {
                    cout << "Jugador " << j.nombreJugador << " conectado con exito al servidor con direccion/hostname: " << host;
                }

                else if(enEspera)
                {
                    cout << "Jugador " << j.nombreJugador << " conectado a la cola de espera del servidor " << host << " con exito";
                }
                else
                {
                    cout << "El Jugador no ha podido ser conectado a ningun servidor activo para el juego indicado por falta de espacio";
                }
            }

        }
        break;

        case 8:
        {

            cadena nick;
            cadena host;
            cout << "Introduzca el nick del jugador a expulsar: " << endl;
            cin.getline(nick,50);

            if(!Gestor.jugadorConectado(nick) && !Gestor.jugadorEnEspera(nick)){
                cout << "El jugador no se encuentra en el sistema" << endl;
            }

            else{
                    Gestor.expulsarJugador(nick,host);
                cout << "Jugador expulsado con exito del servidor: " << host << endl;
            }

        } break;

        case 9:
        {
            cout << "Saliendo del menu..." << endl;
        }
        break;
        default:
        {
            cout << "Opcion incorrecta" << endl;
        }
        }

        cout<<endl;
        PAUSE;
    }
    while(opc != 9);


    return 0;
}
