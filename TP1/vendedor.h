#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>
#include <string>

#include "funcionario.h"
#include "formatacao.h"
#include "venda.h"

using namespace std;

// Classe Vendedor
// Derivada de Funcionario
class Vendedor : public Funcionario {
    vector<Venda*> vendas;

public:
    // Construtor da classe Vendedor
    Vendedor(string = "", string = "", string = "", string = "", string = "", double = 0.);
    // Destrutor da classe Vendedor
    virtual ~Vendedor();

    // Cadastra uma venda do vendedor
    void cadastrarVenda(Venda*);
    // Calcula o valor das vendas do vendedor
    double calcularVendas(int, int);
    // Imprime todas as vendas do vendedor
    void listarVendas();

    // Calcula o salário do vendedor em função das horas trabalhadas, horas pendentes e bonificações
    double calcularSalario(int, int);
    // Exibe o salário do supervisor e a data referente a ele
    void exibirSalario(int, int);
    
    // Sobrecarga do cout para imprimir nome e usuário do vendedor
    friend ostream &operator <<(ostream&, const Vendedor&);
};

#endif