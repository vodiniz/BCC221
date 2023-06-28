#include <iostream>
#include <string>
#include <iomanip>

#include "supervisor.h"
#include "pessoa.h"
#include "venda.h"
#include "data.h"
#include "formatacao.h"

using namespace std;

// Supervisor::Supervisor(string nome, string usuario, string senha, string tipoFuncionario,
//     string funcao, double salarioPorHora) :
//     Funcionario(nome, usuario, senha, tipoFuncionario, funcao, salarioPorHora) {}

// Construtor da classe Supervisor
Supervisor::Supervisor(string nome, string usuario, string senha,
    string tipoFuncionario, string funcao, double SalarioPorHora) :
    Funcionario(nome, usuario, senha, tipoFuncionario, funcao, SalarioPorHora) {}

// Destrutor da classe Supervisor
Supervisor::~Supervisor() {}

// Calcula o salário do supervisor, considerando horas extras, horas pendentes e bonificações
double Supervisor::calcularSalario(int mes, int ano) {

    double vendaTotalSupervisionados = 0.;

    // Varre o vetor de supervisionados e soma o total de vendas de cada um
    // para calcular a bonificação, que é de 1% sobre as vendas
    for(auto vendedor: this->supervisionados)
        vendaTotalSupervisionados += vendedor->calcularVendas(mes, ano);

    double horasMensais = Supervisor::calculaHorasMensais(mes, ano);

    double horaExtra = horasMensais - HORAS_MENSAIS;

    // Se tiver horas extras, diminui das mensais para calcular estas normalmente,
    // já que as horas extras têm bonificação
    if(horaExtra > 0)
        horasMensais -= horaExtra;

    // Se as horas extras forem negativas, reseta para 0, já que não tem
    else
        horaExtra = 0;

    // Retorna o salário com a bonificação de vendas (1) e as horas extras (150%)
    return vendaTotalSupervisionados * .01 + horasMensais 
        * getSalarioPorHora() + horaExtra * getSalarioPorHora() * 2.5;   
}

// Exibe o salário do supervisor e a data referente a ele
void Supervisor::exibirSalario(int mes, int ano) {
    // Aqui usamos setw para padronizar a impressão como MM/AAAA
    // e setfill para preencher com 0 pela esquerda
    cout << Supervisor::getNome() << ":" << endl
        << AZUL << "Salário de " << setw(2) << setfill('0') << mes << "/" << ano << endl
        << "\t" << RESETA << "R$ " << calcularSalario(mes, ano) << "\n" << endl;
}

// Imprime as vendas de todos os vendedores supervisionados pelo supervisor
void Supervisor::listarVendas() {

    if(this->supervisionados.size() == 0){
        cout << VERMELHO_NEGRITO << "Nenhum funcinário cadastrado." << RESETA << "\n" << endl;
        return;
    }
    for(Vendedor *vendedor: this->supervisionados) {
        
        cout << *vendedor << endl;
        vendedor->listarVendas();
        
        if(vendedor != this->supervisionados.back())
            cout << endl << CIANO_NEGRITO << "----------------------------------------" << endl;
    }
}

// Adiciona um funcionário para o supervisor
void Supervisor::adicionarSupervisionado(Vendedor *vendedor) {
    this->supervisionados.push_back(vendedor);
}

// Sobrecarga do cout para imprimir nome e usuário do supervisor
ostream &operator <<(ostream &out, const Supervisor &objeto) {
    out << NEGRITO << objeto.getNome() << RESETA << endl
        << "\t" << NEGRITO << "Usuário: " << RESETA << objeto.getUsuario();
    return out;
}