#include <iostream>
#include <iomanip>
#include <string>

#include "chefe.h"
#include "pessoa.h"
#include "excecao.h"
#include "vendedor.h"
#include "formatacao.h"

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

// Setter e Getter do salario do chefe
void Chefe::setSalarioFixo(double salarioFixo) {
    this->salarioFixo = salarioFixo;
}
double Chefe::getSalarioFixo() const {
    return this->salarioFixo;
}

// Getter para retornar um vetor de funcionario
vector<Funcionario> Chefe::getFuncionarios(){
    return this->funcionarios;
}


// Imprime o salario fixo do chefe
void Chefe::exibeSalario() {
    cout << "\x1b[36mSalário:\x1b[0m R$ " << this->salarioFixo;
}

// Permite ao chefe cadastrar um novo funcionario
void Chefe::cadastrarFuncionario(Funcionario *funcionario) {
    
    // Checa se o nome de usuario ja existe antes de cadastrar o funcionario
    for(auto element: this->funcionarios) {
        if(funcionario->getUsuario() == element.getUsuario()){
            throw UsuarioJaExistente("\x1b[1m\x1b[31mNome de usuário já existente.\x1b[0m", __LINE__);
            return;
        }
    }

    this->funcionarios.push_back(*funcionario);
}

// Imprime todos os funcionarios do chefe
void Chefe::listarFuncionarios() {
    for(auto element: this->funcionarios) {
        cout << element << endl;
    }
}

// Permite ao chefe checar as horas trabalhadas de um funcionario
void Chefe::checarPonto(int mes, int ano) {
    
    for(auto funcionario: this->funcionarios) {
        cout << "--------------------" << endl
        << funcionario << endl // funcionario imprime nome, usuario, tipo e funcao
        << "\t" << "\x1b[34mHoras trabalhadas:\033[0m ";

        // Calcula as horas normais e extra do funcionario
        double horasTrabalhadas = funcionario.calculaHorasMensais(mes, ano);
        double horasExtrasTrabalhadas = (horasTrabalhadas > HORAS_MENSAIS) ? MAXIMO_HORAS_MENSAIS - horasExtrasTrabalhadas : 0;

        if(horasTrabalhadas > HORAS_MENSAIS)
            horasTrabalhadas = HORAS_MENSAIS;
        
        cout << horasTrabalhadas << endl
        << "\t" << "\x1b[32mHoras extras trabalhadas:\033[0m " << horasExtrasTrabalhadas << endl;
        
        if(horasTrabalhadas < 160)
            cout << "\t" << "\x1b[31mHoras pendentes:\033[0m " << HORAS_MENSAIS - horasTrabalhadas << endl;
    }
}

// Permite ao chefe calcular o salario de um funcionario para seu pagamento
double Chefe::calcularSalario(int mes, int ano) {
    // Recebe tipo de funcionario pra ver as bonificacoes
    // Recebe o vetor de ponto do funcionario
    // Caso seja um vendedor, recebe o vetor de vendas
    // Caso seja um supervisor, recebe o vetor de vendas de todos os supervisionado
    
    for(auto funcionario: this->funcionarios) {
        cout << funcionario << endl
            << "\t" << "\x1b[36mSalário:\x1b[0m R$ " << funcionario.calcularSalario(mes, ano) << endl;
    }

    return 0.;
}

// Sobrecarga do cout do chefe
ostream &operator <<(ostream &out, const Chefe &objeto) {
    out << "\x1b[1m\x1b[34m" << objeto.getNome() << "\x1b[0m" << endl
    << "\t" << "\x1b[1mUsuário:\x1b[0m " << objeto.getUsuario() << endl
    << "\t" << "\x1b[1mTipo de funcionário:\x1b[0m " << "Chefe" << endl
    << "\t" << "\x1b[36mSalário:\x1b[0m R$ " << fixed << showpoint << setprecision(2) << objeto.getSalarioFixo() << endl;
        
    return out;
}