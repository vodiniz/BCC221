#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
#include <string>

using namespace std;

// Classe Pessoa
// Base
class Pessoa {
    string nome;

public:
    // Construtor da classe Pessoa
    Pessoa(string = "");
    // Destrutor da classe Pessoa
    virtual ~Pessoa();
    
    // Setter e getter do nome
    void setNome(string);
    string getNome() const;

    // Sobrecarga do cout para imprimir o nome
    friend ostream &operator <<(ostream&, const Pessoa&);
};

#endif