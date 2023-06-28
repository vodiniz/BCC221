#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <iostream>
#include <string>

#include "formatacao.h"
#include "vendedor.h"
#include "venda.h"

using namespace std;

// Classe Supervisor
// Derivada de Funcionario
class Supervisor : public Funcionario {
    vector<Vendedor*> supervisionados; // vetor de vendedores supervisionados

public:
    // Construtor da classe Supervisor
    Supervisor(string = "", string = "", string = "", string = "", string = "", double = 0.);
    // Destrutor da classe Supervisor
    ~Supervisor();

    // Getter dos vendedores supervisionados
    vector<Vendedor*> getVendedores() const;

    // Calcula o salário do supervisor, considerando horas extras, horas pendentes e bonificações
    double calcularSalario(int mes, int ano);
    // Exibe o salário do supervisor e a data referente a ele
    void exibirSalario(int mes, int ano);
    // Imprime as vendas de todos os vendedores supervisionados pelo supervisor
    void listarVendas();
    // Adiciona um funcionário para o supervisor
    void adicionarSupervisionado(Vendedor*);

    // Sobrecarga do cout para imprimir nome e usuário do supervisor
    friend ostream &operator <<(ostream&, const Vendedor&);
};

#endif