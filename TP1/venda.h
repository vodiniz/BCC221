#ifndef VENDA_H
#define VENDA_H

#include <iostream>
#include "data.h"

using namespace std;

// Classe Venda
// Base
class Venda {
    double valor;
    Data data;

public:
    // Construtor da classe Venda
    Venda(double = 0.0, int = 1, int = 1, int = 2023);
    // Destrutor da classe Venda
    virtual ~Venda();

    // Setter e getter do valor
    void setValor(double);
    double getValor() const;

    // Setter e getter da data
    void setData(int, int, int);
    Data getData() const;

    // Sobrecarga do cout para imprimir a data e o valor da venda
    friend ostream& operator <<(ostream&, const Venda&);
};

#endif