#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>
#include <string>

#include "funcionario.h"
#include "venda.h"

using namespace std;

class Vendedor : public Funcionario {
    vector<Venda> vendas;

public:
    Vendedor(string = "", string = "", string = "", string = "", string = "", double = 0.);
    virtual ~Vendedor();
    
    void cadastrarVenda(Venda venda);
    double calcularVendas();
    void listarVendas();

    void exibirSalario();
    
    friend ostream& operator <<(ostream&, const Vendedor&);
};

#endif