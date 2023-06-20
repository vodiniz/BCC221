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
    vector<Ponto> pontos;
    
public:
    Funcionario(string = "", string = "", string = "", string = "", string = "", double = 0.);
    virtual ~Funcionario();

    void setUsuario(string);
    string getUsuario() const;

    void setSenha(string);
    string getSenha() const;

    void setTipoFuncionario(string);
    string getTipoFuncionario() const;

    void setFuncao(string);
    string getFuncao() const;
    
    void cadastrarPonto(Ponto);

    void exibirSalario();
    void listarVendas();

    double calculaHorasSemanais(Data);

    friend ostream& operator <<(ostream&, const Funcionario&);
};

#endif