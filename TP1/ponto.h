#ifndef PONTO_H
#define PONTO_H

#include <iostream>

#include "horario.h"
#include "data.h"

using namespace std;

class Ponto {
    Data dia;
    Horario inicio;
    Horario termino;

public:
    void setData(int, int, int);
    Data getData() const;

    void setHorarioInicio(int, int);
    Horario getHorarioInicio() const;

    void setHorarioTermino(int, int);
    Horario getHorarioTermino() const;

    void calculaHoras();

    friend ostream& operator <<(ostream&, const Ponto&);
};

#endif