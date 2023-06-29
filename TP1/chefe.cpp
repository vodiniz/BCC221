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
Chefe::~Chefe() {
    this->liberaFuncionarios();
}

// Setter e getter do usuário de Chefe
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

// Setter e Getter do salário do chefe
void Chefe::setSalarioFixo(double salarioFixo) {
    this->salarioFixo = salarioFixo;
}
double Chefe::getSalarioFixo() const {
    return this->salarioFixo;
}

// Getter para retornar um vetor de funcionário
vector<Funcionario*> Chefe::getFuncionarios(){
    return this->funcionarios;
}

// Libera os funcionarios que são referenciados pelo vector
void Chefe::liberaFuncionarios(){

    for(Funcionario* funcionario : this->funcionarios)
        delete funcionario;
}

// Imprime o salário fixo do chefe
void Chefe::exibeSalario() {
    cout << CIANO << "Salário: " << RESETA << "R$ " << this->salarioFixo << "\n" << endl;
}

// Permite ao chefe cadastrar um novo funcionário
void Chefe::cadastrarFuncionario(Funcionario *funcionario) {
    
    // Checa se o nome de usuário já existe antes de cadastrar o funcionário
    for(Funcionario* pFuncionario: this->funcionarios) {
        if(funcionario->getUsuario() == pFuncionario->getUsuario()){
            throw UsuarioJaExistente("\x1b[1m\x1b[31mNome de usuário já existente.\x1b[0m", __LINE__);
            return;
        }
    }

    this->funcionarios.push_back(funcionario);
}

// Imprime todos os funcionários do chefe
void Chefe::listarFuncionarios() {
    for(Funcionario *funcionario: this->funcionarios) {
        cout << *funcionario << "\n" << endl;
    }
}

// Permite ao chefe checar as horas trabalhadas de um funcionário
void Chefe::checarPonto(int mes, int ano) {
    
    for(Funcionario *funcionario: this->funcionarios) {
        cout << *funcionario << endl // funcionário imprime nome, usuário, tipo e função
        << "\t" << AZUL << "Horas trabalhadas: " << RESETA;

        // Calcula as horas normais e extras do funcionário
        double horasTrabalhadas = funcionario->calculaHorasMensais(mes, ano);
        double horasExtrasTrabalhadas = (horasTrabalhadas > HORAS_MENSAIS) ? MAXIMO_HORAS_MENSAIS - horasExtrasTrabalhadas : 0;

        if(horasTrabalhadas > HORAS_MENSAIS)
            horasTrabalhadas = HORAS_MENSAIS;
        
        cout << horasTrabalhadas << endl
        << "\t" << VERDE << "Horas extras trabalhadas: " << RESETA << horasExtrasTrabalhadas << endl;
        
        if(horasTrabalhadas < 160)
            cout << "\t" << VERMELHO << "Horas pendentes: " << RESETA << HORAS_MENSAIS - horasTrabalhadas << "\n" << endl;
        
        // if(funcionario != this->funcionarios.back())
        //     cout << NEGRITO << "----------------------------------------" << endl;
    }
}

// Permite ao chefe calcular o salário de um funcionário para seu pagamento
double Chefe::calcularSalario(int mes, int ano) {
    
    for(Funcionario *funcionario: this->funcionarios) {
        cout << *funcionario << endl
            << "\t" << CIANO << "Salário: " << RESETA << "R$ " << funcionario->calcularSalario(mes, ano) << "\n" << endl;
    }

    return 0.;
}

// Sobrecarga do cout do chefe
ostream &operator <<(ostream &out, const Chefe &objeto) {
    out << CIANO_NEGRITO << objeto.getNome() << RESETA << endl
    << "\t" << NEGRITO << "Usuário: " << RESETA << objeto.getUsuario() << endl
    << "\t" << NEGRITO << "Tipo de funcionário: " << RESETA << "Chefe" << endl
    << "\t" << CIANO << "Salário: " << RESETA << "R$ " << fixed << showpoint << setprecision(2) << objeto.getSalarioFixo() << "\n" << endl;
        
    return out;
}