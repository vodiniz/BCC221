#ifndef PONTO_H
#define PONTO_H

#include <iostream>

#include "horario.h"
#include "formatacao.h"
#include "data.h"

using namespace std;

// Classe Ponto
// Base
class Ponto {
    Data dia;
    Horario inicio;
    Horario termino;

public:
    // Construtor da classe Ponto
    Ponto(Data, Horario, Horario);
    // Destrutor da classe Ponto
    virtual ~Ponto();

    // Setter e getter da data
    void setData(Data);
    Data getData() const;

    // Setter e getter do horário de início
    void setHorarioInicio(Horario);
    Horario getHorarioInicio() const;

    // Setter e getter do horário de término
    void setHorarioTermino(Horario);
    Horario getHorarioTermino() const;

    // Calcula a quantidade de horas trabalhadas pelo funcionário em um dia
    double calculaHoras();

    // Sobrecarga do cout para imprimir a data e os horários de entrada e saída
    friend ostream &operator <<(ostream&, const Ponto&);
};

#endif