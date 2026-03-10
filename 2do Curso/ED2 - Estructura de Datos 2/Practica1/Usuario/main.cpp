#include <iostream>
#include "MC.h"

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
    mc.anade(10); // repetido
    mc.anade(30);
    mc.anade(10); // otro repetido
    cout << "Anadidos: 10, 20, 10, 30, 10" << endl;
    cout << "Cardinalidad: " << mc.cardinalidad() << " (esperado: 5)" << endl;
    cout << "esVacio: " << (mc.esVacio() ? "SI" : "NO") << " (esperado: NO)" << endl;

    separador("Pertenece");
    cout << "Pertenece 10: " << (mc.pertenece(10) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 20: " << (mc.pertenece(20) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 30: " << (mc.pertenece(30) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 99: " << (mc.pertenece(99) ? "SI" : "NO") << " (esperado: NO)" << endl;

    separador("Elimina todas las instancias de 10 (hay 3, no consecutivas)");
    mc.elimina(10);
    cout << "Cardinalidad tras eliminar 10: " << mc.cardinalidad() << " (esperado: 2)" << endl;
    cout << "Pertenece 10: " << (mc.pertenece(10) ? "SI" : "NO") << " (esperado: NO)" << endl;
    cout << "Pertenece 20: " << (mc.pertenece(20) ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 30: " << (mc.pertenece(30) ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("Elimina elemento inexistente (no debe crashear)");
    mc.elimina(99);
    cout << "Cardinalidad tras eliminar 99: " << mc.cardinalidad() << " (esperado: 2)" << endl;

    separador("Elimina hasta vaciar");
    mc.elimina(20);
    mc.elimina(30);
    cout << "Cardinalidad: " << mc.cardinalidad() << " (esperado: 0)" << endl;
    cout << "esVacio: " << (mc.esVacio() ? "SI" : "NO") << " (esperado: SI)" << endl;

    // -------------------------------------------------------
    // TEST CASO CRITICO: repetidos CONSECUTIVOS
    // -------------------------------------------------------

    separador("Elimina repetidos CONSECUTIVOS (caso critico del fix)");
    Multiconjunto<int> mc2;
    mc2.anade(5);
    mc2.anade(5);
    mc2.anade(5); // tres seguidos
    mc2.anade(7);
    cout << "Anadidos: 5, 5, 5, 7 | Cardinalidad: " << mc2.cardinalidad() << " (esperado: 4)" << endl;
    mc2.elimina(5);
    cout << "Tras eliminar 5 | Cardinalidad: " << mc2.cardinalidad() << " (esperado: 1)" << endl;
    cout << "Pertenece 5: " << (mc2.pertenece(5) ? "SI" : "NO") << " (esperado: NO)" << endl;
    cout << "Pertenece 7: " << (mc2.pertenece(7) ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("Elimina unico elemento (conjunto de 1)");
    Multiconjunto<int> mc3;
    mc3.anade(42);
    mc3.elimina(42);
    cout << "Cardinalidad: " << mc3.cardinalidad() << " (esperado: 0)" << endl;
    cout << "esVacio: " << (mc3.esVacio() ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("Elimina en conjunto vacio (no debe crashear)");
    Multiconjunto<int> mc4;
    mc4.elimina(1);
    cout << "Cardinalidad: " << mc4.cardinalidad() << " (esperado: 0)" << endl;

    // -------------------------------------------------------
    // TEST CON CHAR
    // -------------------------------------------------------

    separador("TEST CON CHAR - basico");
    Multiconjunto<char> mc5;
    cout << "esVacio: " << (mc5.esVacio() ? "SI" : "NO") << " (esperado: SI)" << endl;
    mc5.anade('a');
    mc5.anade('b');
    mc5.anade('a');
    mc5.anade('c');
    cout << "Anadidos: a, b, a, c | Cardinalidad: " << mc5.cardinalidad() << " (esperado: 4)" << endl;
    cout << "Pertenece 'a': " << (mc5.pertenece('a') ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 'b': " << (mc5.pertenece('b') ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 'z': " << (mc5.pertenece('z') ? "SI" : "NO") << " (esperado: NO)" << endl;

    separador("TEST CON CHAR - elimina");
    mc5.elimina('a');
    cout << "Tras eliminar 'a' | Cardinalidad: " << mc5.cardinalidad() << " (esperado: 2)" << endl;
    cout << "Pertenece 'a': " << (mc5.pertenece('a') ? "SI" : "NO") << " (esperado: NO)" << endl;
    cout << "Pertenece 'b': " << (mc5.pertenece('b') ? "SI" : "NO") << " (esperado: SI)" << endl;
    cout << "Pertenece 'c': " << (mc5.pertenece('c') ? "SI" : "NO") << " (esperado: SI)" << endl;

    separador("TEST CON CHAR - repetidos consecutivos");
    Multiconjunto<char> mc6;
    mc6.anade('x');
    mc6.anade('x');
    mc6.anade('y');
    mc6.anade('x');
    mc6.elimina('x');
    cout << "Tras eliminar 'x' de (x,x,y,x) | Cardinalidad: " << mc6.cardinalidad() << " (esperado: 1)" << endl;
    cout << "Pertenece 'x': " << (mc6.pertenece('x') ? "SI" : "NO") << " (esperado: NO)" << endl;
    cout << "Pertenece 'y': " << (mc6.pertenece('y') ? "SI" : "NO") << " (esperado: SI)" << endl;

    cout << "\n=== FIN DE TESTS ===" << endl;

    return 0;
}
