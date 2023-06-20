#include <iostream>
#include <iomanip>
#include <string>

#include "pessoa.h"
#include "funcionario.h"
#include "vendedor.h"
#include "venda.h"

using namespace std;

// Construtor da classe Vendedor
Vendedor::Vendedor(string nome, string usuario, string senha, string tipoFuncionario,
    string funcao, double salarioPorHora) :
    Funcionario(nome, usuario, senha, tipoFuncionario, funcao, salarioPorHora) {}

// Destrutor da classe Vendedor
Vendedor::~Vendedor() {}

// Cadastra uma venda de um funcionario
void Vendedor::cadastrarVenda(Venda venda) {
    this->vendas.push_back(venda);
}

double Vendedor::calcularVendas() {

    double valorVendas = 0;

    for(auto element: this->vendas) {
        valorVendas += element.getValor();
    }

    return valorVendas;
}

// Imprime o salario do vendedor
// em funcao das horas trabalhadas + bonificacoes, de forma detalhada
void Vendedor::exibirSalario() {

}


// Imprime todas as vendas de um vendedor
void Vendedor::listarVendas() {
    for(auto element: this->vendas) {
        cout << element << "\n";
    }
}

// Sobrecarga do cout para imprimir o horario
ostream& operator <<(ostream& out, const Vendedor& objeto) {
    out << "Nome: " << objeto.getNome() << "\n" <<"Usuário: " << objeto.getUsuario() << "\n";
    return out;
}