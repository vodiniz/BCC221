#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <iostream>
#include <string>
#include <vector>

#include "pessoa.h"
#include "ponto.h"

using namespace std;

class Funcionario : public Pessoa {
    string usuario;
    string senha;
    string tipoFuncionario;
    string funcao;
    double salarioPorHora;
    vector<Ponto> pontos; //pode ser classe vector
    
public:
    void setUsuario(string);
    string getUsuario() const;

    void setSenha(string);
    string getSenha() const;

    void setTipoFuncionario(string);
    string getTipoFuncioario() const;

    void setFuncao(string);
    string getFuncao() const;
    
    void cadastrarPonto();

    virtual double exibirSalario() = 0;
    virtual void listarVenda() = 0;

    void calculaHorasSemanais();

    friend ostream& operator <<(ostream&, const Funcionario&);
};

#endif