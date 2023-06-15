#ifndef HORARIO_H
#define HORARIO_H

#include <iostream>

using namespace std;

class Horario {
    int hora;
    int minuto;

public:
    Horario(int = 0, int = 0);
    ~Horario();

    void setHora();
    int getHora() const;

    void setMinuto(int);
    int getMinuto(int) const;

    friend ostream& operator <<(ostream&, const Horario&);
};

#endif