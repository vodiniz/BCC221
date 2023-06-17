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

    Ponto(Data, Horario, Horario);
    ~Ponto();

    void setData(Data);
    Data getData() const;

    void setHorarioInicio(Horario);
    Horario getHorarioInicio() const;

    void setHorarioTermino(Horario);
    Horario getHorarioTermino() const;

    double calculaHoras();

    friend ostream& operator <<(ostream&, const Ponto&);
};

#endif