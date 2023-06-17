#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <iostream>
#include <string>

#include "vendedor.h"
#include "venda.h"

using namespace std;

class Supervisor : public Funcionario {
    Vendedor *supervisionados;

public:
    friend ostream& operator <<(ostream&, const Vendedor&); // ?
};

#endif