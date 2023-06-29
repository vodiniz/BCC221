#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <iostream>
#include <string>
#include <vector>

#include "pessoa.h"
#include "formatacao.h"
#include "ponto.h"

using namespace std;

// Classe Funcionario
// Derivada de Pessoa
// Herda o atributo nome
class Funcionario : public Pessoa {
    string usuario;
    string senha;
    string tipoFuncionario;
    string funcao;
    double salarioPorHora;
    vector<Ponto*> pontos;

public:
    // Construtor da classe Funcionario
    Funcionario(string = "", string = "", string = "", string = "", string = "", double = 0.);
    // Destrutor da classe Funcionario
    virtual ~Funcionario();

    // Setter e getter do usuário
    void setUsuario(string);
    string getUsuario() const;

    // Setter e getter da senha
    void setSenha(string);
    string getSenha() const;

    // Setter e getter do tipo de usuário
    void setTipoFuncionario(string);
    string getTipoFuncionario() const;

    // Setter e getter da função
    void setFuncao(string);
    string getFuncao() const;

    // Setter e getter do salário
    void setSalarioPorHora(double);
    double getSalarioPorHora() const;

    // Cadastra o ponto diário do funcionário
    void cadastrarPonto(Ponto*);
    
    // Libera os pontos que são referenciados pelo vector
    void liberaPontos();

    // Funções virtuais para as classes derivadas herdarem e manipularem
    virtual double calcularSalario(int, int);
    virtual void exibirSalario(int, int);
    virtual void listarVendas();

    // Calcula a quantidade de horas trabalhadas pelo funcionário em uma semana
    double calculaHorasSemanais(Data);
    // Calcula a quantidade de horas trabalhadas pelo funcionário em um mês
    double calculaHorasMensais(int, int);

    // Sobrecarga do cout para imprimir os dados do funcionário
    friend ostream &operator<<(ostream &, const Funcionario &);
};

#endif