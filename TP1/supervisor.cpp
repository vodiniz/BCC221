#include <iostream>
#include <string>
#include <iomanip>

#include "supervisor.h"
#include "pessoa.h"
#include "venda.h"
#include "data.h"

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

// Calcula o salario do supervisor, considerando horas extra, horas pendentes e bonificacoes
double Supervisor::calcularSalario(int mes, int ano) {

    double vendaTotalSupervisionados = 0.;

    // Varre o vetor de supervisionados e soma o total de vendas de cada um
    // para calcular a bonificacao, que eh de 1% sobre as vendas
    for(auto vendedor: this->supervisionados)
        vendaTotalSupervisionados += vendedor.calcularVendas(mes, ano);

    double horasMensais = Supervisor::calculaHorasMensais(mes, ano);

    double horaExtra = horasMensais - 40;

    // Se tiver horas extra, diminui das mensais para calcular estas normalmente,
    // ja que as horas extra tem bonificacao
    if(horaExtra > 0)
        horasMensais -= horaExtra;

    // Se as horas extra forem negativas, reseta para 0, ja que nao tem
    else
        horaExtra = 0;

    // Retorna o salario com a bonificacao de vendas (1) e as horas extra (150%)
    return vendaTotalSupervisionados * .01 + horasMensais 
        * getSalarioPorHora() + horaExtra * getSalarioPorHora() * 2.5;   
}

// Exibe o salario do supervisor e a data referente a ele
void Supervisor::exibirSalario(int mes, int ano) {
    // Aqui usamos setw para padronizar a impressao como MM/AAAA
    // e setfill para preencher com 0 pela esquerda
    cout << Supervisor::getNome() << ":" << endl
        << "Salário de " << setw(2) << setfill('0') << mes << "/" << ano << endl
        << "R$ " << calcularSalario(mes, ano);
}

// Imprime as vendas de todos os vendedores supervisionados pelo supervisor
void Supervisor::listarVendas() {
    for(auto vendedor: this->supervisionados) {
        cout << vendedor << endl;
        vendedor.listarVendas();
        cout << endl << "--------------------";
    }
}

// Adiciona um funcionario para o supervisor
void Supervisor::adicionarSupervisionado(Vendedor *vendedor){
    this->supervisionados.push_back(*vendedor);
}

// Sobrecarga do cout para imprimir nome e usuario do supervisor
ostream& operator <<(ostream &out, const Supervisor &objeto) {
    out << "Nome: " << objeto.getNome() << endl
        << "Usuário: " << objeto.getUsuario();
    return out;
}