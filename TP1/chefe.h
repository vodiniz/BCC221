#ifndef CHEFE_H
#define CHEFE_H

#include <iostream>
#include <string>

#include "pessoa.h"
#include "funcionario.h"
#include "formatacao.h"

using namespace std;

// Classe Chefe
// Derivada de Pessoa
// Herda o atributo nome
class Chefe : public Pessoa {
    string usuario;
    string senha;
    double salarioFixo; // como o chefe não bate ponto, seu salário é fixo
    vector<Funcionario*> funcionarios; // vetor com todos seus funcionários

public:
    // Construtor da classe Chefe
    Chefe(string = "", string = "", string = "", double = 0.);
    // Destrutor da classe Chefe
    virtual ~Chefe();

    // Setter e getter do usuário do chefe
    void setUsuario(string);
    string getUsuario() const;

    // Setter e getter da senha do chefe
    void setSenha(string);
    string getSenha() const;

    // Setter e getter do salário do chefe
    void setSalarioFixo(double);
    double getSalarioFixo() const;

    // Getter dos funcionários listados
    vector<Funcionario*> getFuncionarios();

    // Imprime o salário fixo do chefe
    void exibeSalario();
    // Permite ao Chefe cadastrar um novo funcionário
    void cadastrarFuncionario(Funcionario*);
    // Imprime todos os funcionários do chefe
    void listarFuncionarios();
    // Permite ao chefe checar as horas trabalhadas de um funcionário
    void checarPonto(int, int);
    // Permite ao chefe calcular o salário de um funcionário para seu pagamento
    double calcularSalario(int, int);

    // Sobrecarga do cout do chefe
    friend ostream &operator <<(ostream&, const Chefe&);
};

#endif