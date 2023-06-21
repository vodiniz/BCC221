#ifndef CHEFE_H
#define CHEFE_H

#include <iostream>
#include <string>

#include "pessoa.h"
#include "funcionario.h"

using namespace std;

// Classe Chefe
// Derivada de Pessoa
// Herda o atributo nome
class Chefe : public Pessoa {
    string usuario;
    string senha;
    double salarioFixo; // como o chefe nao bate ponto, seu salario eh fixo
    vector<Funcionario> funcionarios; // vetor com todos seus funcionarios

public:
    // Construtor da classe Chefe
    Chefe(string = "", string = "", string = "", double = 0.);
    // Destrutor da classe Chefe
    virtual ~Chefe();

    // Setter e Getter do usuario do chefe
    void setUsuario(string);
    string getUsuario() const;

    // Setter e Getter da senha do chefe
    void setSenha(string);
    string getSenha() const;

    // Permite ao Chefe cadastrar um novo funcionario
    void cadastrarFuncionario(Funcionario*);
    // Imprime todos os funcionarios do Chefe
    void listarFuncionarios();
    // Permite ao Chefe checar as horas trabalhadas de um funcionario
    void checarPonto(int, int);
    // Permite ao Chefe calcular o salario de um funcionario para seu pagamento
    double calcularSalario(int, int);
};

#endif