#include <iostream>

using namespace std;

int main()
{
    int Nalum,Nota,Nsus=0,Nap=0,Nnot=0,Nsob=0;
    cout << "Introduzca el numero de alumnos examinados: " << endl;
    cin >> Nalum;
    for(int i=0;i<Nalum;i++){
        do {
        cout << "Introduzca la nota del alumno " << i+1 << endl;
        cin >> Nota;
        if(Nota<0 || Nota>10){
            cout << "Error, debe estar entre [0,10]" << endl;
        }
        }while(Nota<0 || Nota >10);
        if(Nota<5)
            Nsus++;
        else if(Nota>=5 && Nota<7)
            Nap++;
        else if(Nota>=7 && Nota <9)
            Nnot++;
        else if(Nota>=9 && Nota<=10)
            Nsob++;
    }
    cout << "Numero de alumnos presentados: " << Nalum
         << "\nNumero de suspensos: " << Nsus
         << "\nNumero de aprobados: " << Nap
         << "\nNumero de notables: " << Nnot
         << "\nNumero de sobresalientes: " << Nsob << endl;
    return 0;
}
