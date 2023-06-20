#ifndef CHEFE_H
#define CHEFE_H

#include <iostream>
#include <string>

#include "pessoa.h"
#include "horario.h"
#include "funcionario.h"
#include "ponto.h"

using namespace std;

class Chefe : public Pessoa {
    string usuario;
    string senha;
    string funcao;
    double salarioPorHora;
    vector<Funcionario> funcionarios;

public:
    Chefe(string = "", string = "", string = "", string = "", double = 0.);
    virtual ~Chefe();

    void setUsuario(string);
    string getUsuario() const;

    void setSenha(string);
    string getSenha() const;

    void setFuncao(string);
    string getFuncao() const;

    void cadastrarFuncionario(Funcionario*);
    void listarFuncionarios();
    void checarPonto();
    double calcularSalario();
};

#endif