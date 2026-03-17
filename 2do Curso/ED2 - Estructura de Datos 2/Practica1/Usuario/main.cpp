#include <iostream>
#include "MC.h"
#include "Persona.h"

using namespace std;

void separador(const string& titulo)
{
    cout << "\n=== " << titulo << " ===" << endl;
}

int main()
{
    // -------------------------------------------------------
    // TEST CON INT
    // -------------------------------------------------------

    separador("Constructor / esVacio");
    Multiconjunto<int> mc;
    cout << "Recien creado, esVacio: " << (mc.esVacio() ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Cardinalidad: " << mc.cardinalidad() << " (esperado: 0)" << endl;

    separador("Anade elementos (con repetidos)");
    mc.anade(10);
    mc.anade(20);
    mc.anade(10);
    mc.anade(30);
    mc.anade(10);
    cout << "Anadidos: 10, 20, 10, 30, 10" << endl;
    cout << "Cardinalidad: " << mc.cardinalidad() << " (esperado: 5)" << endl;
    cout << "esVacio: " << (mc.esVacio() ? "SI" : "NO") << " (esperado: NO)" << endl;

    separador("Pertenece");
    cout << "Pertenece 10: " << (mc.pertenece(10) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 20: " << (mc.pertenece(20) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 99: " << (mc.pertenece(99) ? "SI" : "NO") << " (esperado: NO)" << endl;

    separador("Elimina todas las instancias de 10 (hay 3, no consecutivas)");
    mc.elimina(10);
    cout << "Cardinalidad tras eliminar 10: " << mc.cardinalidad() << " (esperado: 2)" << endl;
    cout << "Pertenece 10: " << (mc.pertenece(10) ? "SI" : "NO") << " (esperado: NO)" << endl;

    separador("Elimina elemento inexistente");
    mc.elimina(99);
    cout << "Cardinalidad: " << mc.cardinalidad() << " (esperado: 2)" << endl;

    separador("Elimina hasta vaciar");
    mc.elimina(20);
    mc.elimina(30);
    cout << "Cardinalidad: " << mc.cardinalidad() << " (esperado: 0)" << endl;
    cout << "esVacio: " << (mc.esVacio() ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("Repetidos CONSECUTIVOS (caso critico)");
    Multiconjunto<int> mc2;
    mc2.anade(5); mc2.anade(5); mc2.anade(5); mc2.anade(7);
    mc2.elimina(5);
    cout << "Cardinalidad tras eliminar 5 de (5,5,5,7): " << mc2.cardinalidad() << " (esperado: 1)" << endl;
    cout << "Pertenece 5: " << (mc2.pertenece(5) ? "SI" : "NO") << " (esperado: NO)" << endl;
    cout << "Pertenece 7: " << (mc2.pertenece(7) ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("Elimina en conjunto vacio");
    Multiconjunto<int> mc3;
    mc3.elimina(1);
    cout << "Cardinalidad: " << mc3.cardinalidad() << " (esperado: 0)" << endl;

    // -------------------------------------------------------
    // TEST CON CHAR
    // -------------------------------------------------------

    separador("TEST CON CHAR - basico");
    Multiconjunto<char> mc4;
    mc4.anade('a'); mc4.anade('b'); mc4.anade('a'); mc4.anade('c');
    cout << "Anadidos: a, b, a, c | Cardinalidad: " << mc4.cardinalidad() << " (esperado: 4)" << endl;
    cout << "Pertenece 'a': " << (mc4.pertenece('a') ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 'z': " << (mc4.pertenece('z') ? "SI" : "NO") << " (esperado: NO)" << endl;

    separador("TEST CON CHAR - elimina");
    mc4.elimina('a');
    cout << "Cardinalidad tras eliminar 'a': " << mc4.cardinalidad() << " (esperado: 2)" << endl;
    cout << "Pertenece 'a': " << (mc4.pertenece('a') ? "SI" : "NO") << " (esperado: NO)" << endl;
    cout << "Pertenece 'b': " << (mc4.pertenece('b') ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("TEST CON CHAR - repetidos consecutivos");
    Multiconjunto<char> mc5;
    mc5.anade('x'); mc5.anade('x'); mc5.anade('y'); mc5.anade('x');
    mc5.elimina('x');
    cout << "Cardinalidad tras eliminar 'x' de (x,x,y,x): " << mc5.cardinalidad() << " (esperado: 1)" << endl;
    cout << "Pertenece 'x': " << (mc5.pertenece('x') ? "SI" : "NO") << " (esperado: NO)" << endl;
    cout << "Pertenece 'y': " << (mc5.pertenece('y') ? "SI" : "NO") << " (esperado: SI)" << endl;

    // -------------------------------------------------------
    // TEST CON PERSONA
    // -------------------------------------------------------

    Persona ana("Ana", 25);
    Persona luis("Luis", 30);
    Persona marta("Marta", 22);
    Persona anadup("Ana", 25); // igual que ana, para probar operator==

    separador("TEST CON PERSONA - constructor / esVacio");
    Multiconjunto<Persona> mcp;
    cout << "esVacio: " << (mcp.esVacio() ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Cardinalidad: " << mcp.cardinalidad() << " (esperado: 0)" << endl;

    separador("TEST CON PERSONA - anade");
    mcp.anade(ana);
    mcp.anade(luis);
    mcp.anade(ana);   // repetido
    mcp.anade(marta);
    mcp.anade(ana);   // otro repetido
    cout << "Anadidos: Ana, Luis, Ana, Marta, Ana" << endl;
    cout << "Cardinalidad: " << mcp.cardinalidad() << " (esperado: 5)" << endl;
    cout << "esVacio: " << (mcp.esVacio() ? "SI" : "NO") << " (esperado: NO)" << endl;

    separador("TEST CON PERSONA - pertenece");
    cout << "Pertenece Ana(25): " << (mcp.pertenece(ana) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece anadup (copia igual a Ana): " << (mcp.pertenece(anadup) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece Luis(30): " << (mcp.pertenece(luis) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece Persona inexistente: " << (mcp.pertenece(Persona("Nadie", 99)) ? "SI" : "NO") << " (esperado: NO)" << endl;

    separador("TEST CON PERSONA - elimina (3 instancias de Ana)");
    mcp.elimina(ana);
    cout << "Cardinalidad tras eliminar Ana: " << mcp.cardinalidad() << " (esperado: 2)" << endl;
    cout << "Pertenece Ana: " << (mcp.pertenece(ana) ? "SI" : "NO") << " (esperado: NO)" << endl;
    cout << "Pertenece Luis: " << (mcp.pertenece(luis) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece Marta: " << (mcp.pertenece(marta) ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("TEST CON PERSONA - elimina inexistente");
    mcp.elimina(Persona("Nadie", 99));
    cout << "Cardinalidad: " << mcp.cardinalidad() << " (esperado: 2)" << endl;

    separador("TEST CON PERSONA - repetidos consecutivos");
    Multiconjunto<Persona> mcp2;
    mcp2.anade(ana); mcp2.anade(ana); mcp2.anade(ana); mcp2.anade(luis);
    mcp2.elimina(ana);
    cout << "Cardinalidad tras eliminar Ana de (Ana,Ana,Ana,Luis): " << mcp2.cardinalidad() << " (esperado: 1)" << endl;
    cout << "Pertenece Ana: " << (mcp2.pertenece(ana) ? "SI" : "NO") << " (esperado: NO)" << endl;
    cout << "Pertenece Luis: " << (mcp2.pertenece(luis) ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("TEST CON PERSONA - vaciar");
    mcp.elimina(luis);
    mcp.elimina(marta);
    cout << "Cardinalidad: " << mcp.cardinalidad() << " (esperado: 0)" << endl;
    cout << "esVacio: " << (mcp.esVacio() ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("TEST CON PERSONA - operator<<");
    cout << "Persona ana: " << ana << endl;
    cout << "Persona luis: " << luis << endl;
    cout << "Persona marta: " << marta << endl;

    cout << "\n=== FIN DE TESTS ===" << endl;

    return 0;
}
