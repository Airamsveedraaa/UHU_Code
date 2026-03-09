#include <iostream> //cin cout
#include <windows.h> //system("cls")
#include <cstdlib> //rand srand(time(0))
#include <ctime> //time(0)
#define NAsignaturas 5
#define NEstudiantes 10

using namespace std;

int main()
{
    srand(time(0));
    float Notas[NAsignaturas][NEstudiantes]; //Almacena notas de cada estudiante en cada asignatura
    int opc;
    int aprob=0;
    int alum;
    float media,suma;
    int Nasig;
    do
    {

        cout << "     MENU     "
             << "\n1.Rellenar Datos"
             << "\n2.Mostrar aprobados por asignatura"
             << "\n3.Consultar notas alumno"
             << "\n4.Consultar media asignatura"
             << "\n5.Salir"
             << "\nSeleccione una opcion: " << endl;
        cin >> opc;
        cin.ignore();
        system("cls");

        switch(opc)
        {

        case 1:
            for(int i=0; i<NAsignaturas; i++)
            {
                for(int j=0; j<NEstudiantes; j++)
                {
                    Notas[i][j]=rand()%101/10.0;
                }
            }
            cout << "Notas: ";
            for(int i=0; i<NAsignaturas; i++)
            {
                cout << "\nAsignatura: " << i+1;
                for(int j=0; j<NEstudiantes; j++)
                {
                    cout << "\n" << Notas[i][j] << endl;
                }
            }

            break;

        case 2:
            for(int i=0; i<NAsignaturas; i++)
            {
                cout << "Asignatura " << i+1 << ":";

                aprob=0;
                for(int j=0; j<NEstudiantes; j++)
                {
                    if(Notas[i][j]>=5.0)
                    {
                        aprob++; //Funciona, pero no del todo correctamente,incrementa siempre que
                                 //sea mayor o igual que 5.0, pero para la asignatura 2 mostrara
                                 //Los aprobados de la asignatura anterior y los de esa, si la
                                 //1 tiene 5 aprobados y la 2 tiene 6 aprobados, mostrar� para la 1, 5 aprobados, y para la 2, 11 aprobados

                    }
                }
                cout << aprob << " Aprobados";
                if(i<NAsignaturas-1){
                    cout << ", ";
                }

            }
            cout << endl;

            break;

        case 3:
            do
            {
                cout << "Introduzca el numero de un alumno: " << endl;
                cin >> alum;
                if(alum<0 || alum>9)
                {
                    cout << "No existe ningun alumno con ese numero, introduzcalo de nuevo." << endl;
                }
            }
            while(alum<0 || alum > 9);

            cout << "Notas del estudiante " << alum+1<<":" << endl;
            for(int i=0; i<NAsignaturas; i++)
            {
                cout << Notas[i][alum] << endl;
            }

            break;

        case 4:

            do{
                cout << "Introduzca el numero de la asignatura a mostar medias: " << endl;
                cin >> Nasig;
                if(Nasig<0 ||Nasig>4){
                    cout << "No existe ninguna asignatura con ese numero, introduzcalo de nuevo" << endl;
                }
            }while(Nasig<0 || Nasig>4);
            suma=0.0;
            for(int i=0;i<NEstudiantes;i++){
                suma+=Notas[Nasig][i];
                media=suma/NEstudiantes;
            }

            cout << "Nota media de la asignatura " << Nasig+1 << ": "
                 << "\n" << media << endl;

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
