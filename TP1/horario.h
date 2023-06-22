#ifndef HORARIO_H
#define HORARIO_H

#include <iostream>

using namespace std;

// Classe Horario
// Base
class Horario {
    int hora;
    int minuto;

public:
    // Construtor da classe Horario
    Horario(int = 0, int = 0);
    // Destrutor da classe Horario
    virtual ~Horario();

    // Setter e getter da hora
    void setHora(int);
    int getHora() const;

    // Setter e getter do minuto
    void setMinuto(int);
    int getMinuto() const;

    // Sobrecarga do cout para imprimir o horario
    friend ostream &operator <<(ostream&, const Horario&);
};

#endif