#ifndef VENDA_H
#define VENDA_H

#include <iostream>

using namespace std;

class Venda {
    double valor;

public:
    Venda(double = 0.0);
    ~Venda();

    void setValor(double);
    double getValor() const;

    friend ostream& operator <<(ostream&, const Venda&);
};

#endif