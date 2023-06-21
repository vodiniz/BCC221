#include <iostream>
#include <iomanip>
#include <string>

#include "chefe.h"
#include "pessoa.h"
#include "excecao.h"
#include "vendedor.h"

using namespace std;

// Construtor da classe Chefe
Chefe::Chefe(string nome, string usuario, string senha, double salarioFixo) :
    Pessoa(nome), usuario(usuario), senha(senha), salarioFixo(salarioFixo) {}

// Destrutor da classe Chefe
Chefe::~Chefe() {}

// Setter e getter do usuario de Chefe
void Chefe::setUsuario(string usuario) {
    this->usuario = usuario;
}
string Chefe::getUsuario() const {
    return this->usuario;
}

// Setter e getter da senha de Chefe
void Chefe::setSenha(string senha) {
    this->senha = senha;
}
string Chefe::getSenha() const {
    return this->senha;
}

// Permite ao Chefe cadastrar um novo funcionario
void Chefe::cadastrarFuncionario(Funcionario *funcionario) {
    
    // Checa se o nome de usuario ja existe antes de cadastrar o funcionario
    for(auto element: this->funcionarios) {
        if(funcionario->getUsuario() == element.getUsuario()){
            throw UsuarioJaExistente("\033[31mNome de usuário já existente.", __LINE__);
            return;
        }
    }

    this->funcionarios.push_back(*funcionario);
}

// Imprime todos os funcionarios do Chefe
void Chefe::listarFuncionarios() {
    for(auto element: this->funcionarios) {
        cout << element << "\n";
    }
}

// Permite ao Chefe checar as horas trabalhadas de um funcionario
void Chefe::checarPonto(int mes, int ano) {
    
    for(auto funcionario: this->funcionarios) {
        cout << "--------------------" << endl
        << funcionario << endl // funcionario imprime nome, usuario, tipo e funcao
        << "Horas trabalhadas: ";

        // Calcula as horas normais e extra do funcionario
        double horasTrabalhadas = funcionario.calculaHorasMensais(mes, ano);
        double horasExtrasTrabalhadas = (horasTrabalhadas > 160) ? 200 - horasExtrasTrabalhadas : 0;

        if(horasTrabalhadas > 160)
            horasTrabalhadas = 160;
        
        cout << horasTrabalhadas << endl
        << "Horas extras trabalhadas: " << horasExtrasTrabalhadas << endl;
        
        if(horasTrabalhadas < 160)
            cout << "Horas pendentes: " << 160 - horasTrabalhadas << endl;
    }
}

// Permite ao Chefe calcular o salario de um funcionario para seu pagamento
double Chefe::calcularSalario(int mes, int ano) {
    // Recebe tipo de funcionario pra ver as bonificacoes
    // Recebe o vetor de ponto do funcionario
    // Caso seja um vendedor, recebe o vetor de vendas
    // Caso seja um supervisor, recebe o vetor de vendas de todos os supervisionado
    
    for(auto funcionario: this->funcionarios) {
        cout << funcionario << endl
            << "\t" << "Salário: " << funcionario.calcularSalario(mes,ano);
    }

    return 0.;
}