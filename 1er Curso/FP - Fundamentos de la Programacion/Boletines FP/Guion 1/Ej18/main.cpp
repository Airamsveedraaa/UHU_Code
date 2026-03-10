#include <iostream>

using namespace std;

int main()
{
    float retencion;
    int horasN,horasEx;
    cout << "Introduzca las horas trabajadas y las horas extras trabajadas en ese orden: " << endl;
    cin >> horasN >> horasEx;
    float sueldo_sin_retencion= (horasN*5)+(horasEx*8);
    retencion= sueldo_sin_retencion*0.15;
    float sueldo_final= sueldo_sin_retencion - retencion;
    cout << "Su sueldo sera de: " << sueldo_final << " Euros"  << endl;
    return 0;
}
