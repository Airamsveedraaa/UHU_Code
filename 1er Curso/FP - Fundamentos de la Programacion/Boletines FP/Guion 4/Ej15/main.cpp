#include <iostream>
#include <cstring>
#include <conio.h>
#include <cctype>
using namespace std;

typedef char cadena[25];

class PalabraOculta
{

private:
    char palabraSecreta[25];
    char palabraJugada[25];
    int Puntos;

public:
    void Iniciar();
    bool Jugada(char letra);
    int getPuntos();
    void MostrarJugada();
    void DescubrirSecreta();

};


void PalabraOculta::Iniciar()
{
    char c;
    int i = 0;
    bool palabraCompleta = false;

    cout << "Introduce la palabra oculta (no se mostrara por pantalla) " << endl;

    while (i < 25 && !palabraCompleta)
    {
        c = getch();
        if (c == '\r')
        {
            palabraSecreta[i] = '\0';
            palabraCompleta = true;
        }
        else
        {
            palabraSecreta[i] = toupper(c);
            cout << '*';
            i++;
        }
    }

    if (i < 25 && !palabraCompleta)
    {
        palabraSecreta[i] = '\0';
    }

    for (int j = 0; j < i; j++)
    {
        palabraJugada[j] = '-';
    }
    palabraJugada[i] = '\0';

    Puntos = 9;

    cout << "\nPalabra lista para jugar, suerte :)" << endl;
}

bool PalabraOculta::Jugada(char letra)
{

    bool adivinada=false;
    bool letraencontrada=false;
    char c;
    int longi=strlen(palabraSecreta);
    int i=0;

    for(int i=0; i<longi; i++)
    {
        if(palabraSecreta[i]==toupper(letra))
        {
            palabraJugada[i]=palabraSecreta[i];
            letraencontrada=true;
        }
    }
    if(!letraencontrada)
        Puntos--;

    if(strcmp(palabraSecreta,palabraJugada)==0)
        adivinada=true;

    return adivinada;

}

int PalabraOculta::getPuntos(){

return Puntos;
}

void PalabraOculta::MostrarJugada(){

cout << palabraJugada << endl;

}

void PalabraOculta::DescubrirSecreta(){


cout << palabraSecreta << endl;
}


int main()
{
    PalabraOculta juego;
    char letra;
    bool juegoTerminado = false;

    juego.Iniciar();
    juego.MostrarJugada();

    while (!juegoTerminado && juego.getPuntos() > 0)
    {
        cout << "Introduzca una letra: ";
        cin >> letra;  // Pedir al jugador una letra

        if (juego.Jugada(letra))
        {
            cout << "Felicidades, acertaste! La palabra era: ";
            juego.DescubrirSecreta();
            cout << "Obtuviste un total de " << juego.getPuntos() << " puntos." << endl;
            juegoTerminado = true;
        }
        else
        {
            juego.MostrarJugada();  // Mostrar el progreso de la palabra jugada
            cout << "Te quedan " << juego.getPuntos() << " puntos." << endl;
            if (juego.getPuntos() == 0)
            {
                cout << "Juego terminado, no te quedan puntos!" << endl;
                juegoTerminado = true;
            }
        }
    }

    return 0;
}
