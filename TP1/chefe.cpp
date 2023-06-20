#include <iostream>
#include <iomanip>
#include <string>

#include "chefe.h"
#include "pessoa.h"

using namespace std;

// Construtor da classe Chefe
Chefe::Chefe(string nome, string usuario, string senha, string funcao, double salarioHora) :
    Pessoa(nome), usuario(usuario), senha(senha),
    funcao(funcao), salarioPorHora(salarioPorHora) {}

// Destrutor da classe Chefe
Chefe::~Chefe() {}

// Setter e getter do usuario
void Chefe::setUsuario(string usuario) {
    this->usuario = usuario;
}
string Chefe::getUsuario() const {
    return this->usuario;
}

// Setter e getter da senha
void Chefe::setSenha(string senha) {
    this->senha = senha;
}
string Chefe::getSenha() const {
    return this->senha;
}

// Setter e getter da funcao
void Chefe::setFuncao(string funcao) {
    this->funcao = funcao;
}
string Chefe::getFuncao() const {
    return this->funcao;
}

void Chefe::cadastrarFuncionario(Funcionario *funcionario) {
    this->funcionarios.push_back(*funcionario);
}

void Chefe::listarFuncionarios() {
    for(auto element: this->funcionarios) {
        cout << element << "\n";
    }
}

void Chefe::checarPonto() {

}

double Chefe::calcularSalario() {

}

ostream& operator <<(ostream& out, const Chefe& objeto) {
    out << "Nome: " << objeto.getNome() << "\n";
    return out;
}