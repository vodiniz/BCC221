#include <iostream>
#include <string>

#include "funcionario.h"
#include "venda.h"

using namespace std;

class Vendedor : public Funcionario {
    Venda *vendas;

public:
    Vendedor();
    ~Vendedor();
    void cadastrarVenda();
    friend ostream& operator <<(ostream&, const Vendedor&);
};