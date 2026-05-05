#ifndef __PERSONA_H__
#define __PERSONA_H__
#include <string>
#include <iostream>

using namespace std;

class Persona
{
public:
    Persona(const string& n = "", int e = 0);
    const string& getNombre() const;
    int getEdad() const;
    void setNombre(const string& n);
    void setEdad(int e);
    bool operator==(const Persona& p) const;
private:
    string nombre;
    int edad;
};

ostream& operator<<(ostream& s, const Persona& p);

#endif // __MAIN_H__
