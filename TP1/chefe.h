#ifndef CHEFE_H
#define CHEFE_H

#include <iostream>
#include <string>

#include "pessoa.h"
#include "horario.h"
#include "funcionario.h"

using namespace std;

class Chefe : public Pessoa {
    string usuario;
    string senha;
    string funcao;
    Funcionario *funcionarios;
    double salarioPorHora;
    int *ponto; //pode ser classe vector, pesquisar.
    
public:
    void setUsuario(string);
    string getUsuario() const;

    void setSenha(string);
    string getSenha() const;

    void setFuncao(string);
    string getFuncao() const;

    double calculaSalario();
};

#endif