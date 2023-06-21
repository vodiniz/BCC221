#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>
#include <string>

#include "funcionario.h"
#include "venda.h"

using namespace std;

// Classe Vendedor
// Derivada de Funcionario
class Vendedor : public Funcionario {
    vector<Venda> vendas;

public:
    // Construtor da classe Vendedor
    Vendedor(string = "", string = "", string = "", string = "", string = "", double = 0.);
    // Destrutor da classe Vendedor
    virtual ~Vendedor();

    // Cadastra uma venda do vendedor
    void cadastrarVenda(Venda);
    // Calcula o valor das vendas do vendedor
    double calcularVendas(int, int);
    // Imprime todas as vendas do vendedor
    void listarVendas();

    // Calcula o salario do vendedor em funcao das horas trabalhadas, horas pendentes e bonificacoes
    double calcularSalario(int, int);
    // Exibe o salario do supervisor e a data referente a ele
    void exibirSalario(int, int);
    
    // Sobrecarga do cout para imprimir nome e usuario do vendedor
    friend ostream& operator <<(ostream&, const Vendedor&);
};

#endif