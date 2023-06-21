#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <iostream>
#include <string>

#include "vendedor.h"
#include "venda.h"

using namespace std;

// Classe Supervisor
// Derivada de Funcionario
class Supervisor : public Funcionario {
    vector<Vendedor> supervisionados; // vetor de vendedores supervisores

public:
    // Construtor da classe Supervisor
    Supervisor(string = "", string = "", string = "", string = "", string = "", double = 0.);
    // Destrutor da classe Supervisor
    ~Supervisor();

    // Calcula o salario do supervisor, considerando horas extra, horas pendentes e bonificacoes
    double calcularSalario(int mes, int ano);
    // Exibe o salario do supervisor e a data referente a ele
    void exibirSalario(int mes, int ano);
    // Imprime as vendas de todos os vendedores supervisionados pelo supervisor
    void listarVendas();
    // Adiciona um funcionario para o supervisor
    void adicionarSupervisionado(Vendedor*);

    // Sobrecarga do cout para imprimir nome e usuario do supervisor
    friend ostream& operator <<(ostream&, const Vendedor&);
};

#endif