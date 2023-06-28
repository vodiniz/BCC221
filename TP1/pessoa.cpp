#include <iostream>
#include <string>

#include "pessoa.h"

using namespace std;

// Construtor da classe Pessoa
Pessoa::Pessoa(string nome) :
    nome(nome) {}

// Destrutor da classe Pessoa
Pessoa::~Pessoa() {}

// Setter e getter do nome
void Pessoa::setNome(string nome) {
    this->nome = nome;
}
string Pessoa::getNome() const {
    return this->nome;
}

// Sobrecarga do cout para imprimir o nome da pessoa
ostream &operator <<(ostream &out, const Pessoa &objeto) {
    out << CIANO_NEGRITO << "Nome: " << RESETA << objeto.getNome();
    return out;
}