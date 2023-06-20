#include <iostream>
#include <iomanip>

#include "pessoa.h"
#include "funcionario.h"
#include "excecao.h"
#include "data.h"

using namespace std;

Funcionario::Funcionario(string nome, string usuario, string senha, 
    string tipoFuncionario, string funcao, double salarioPorHora) :
    Pessoa(nome), usuario(usuario), senha(senha), tipoFuncionario(tipoFuncionario),
    funcao(funcao), salarioPorHora(salarioPorHora) {}

Funcionario::~Funcionario() {}

// Setter e getter do usuario
void Funcionario::setUsuario(string usuario) {
    this->usuario = usuario;
}
string Funcionario::getUsuario() const {
    return this->usuario;
}

// Setter e getter da senha
void Funcionario::setSenha(string senha) {
    this->senha = senha;
}
string Funcionario::getSenha() const {
    return this->senha;
}

// Setter e getter do tipo de funcionario
void Funcionario::setTipoFuncionario(string tipoFuncionario) {
    this->tipoFuncionario = tipoFuncionario;
}
string Funcionario::getTipoFuncionario() const {
    return this->tipoFuncionario;
}

// Setter e getter da funcao
void Funcionario::setFuncao(string funcao) {
    this->funcao = funcao;
}
string Funcionario::getFuncao() const {
    return this->funcao;
}

// Cadastra o ponto diario do funcionario
void Funcionario::cadastrarPonto(Ponto ponto) {
    
    double horasSemanais = calculaHorasSemanais(ponto.getData());
    double horasUteis;
    
    // Impede o funcionario de cadastrar um ponto se ja tiver chegado ao limite
    if(horasSemanais >= 50)
        throw HorasExcedidas("Você já trabalhou 50 horas essa semana.", __LINE__);

    // Caso o funcionario tente cadastrar um ponto que ultrapasse o limite,
    // cadastra o maximo de tempo que pode sem estourar.
    else if(horasSemanais + ponto.calculaHoras() > 50) {
        
        horasUteis = 50 - horasSemanais; // maximo de horas que podem ser cadastradas
        Horario hora = ponto.getHorarioInicio();
        
        // O horario de inicio do ponto nao sera alterado
        // O horario de termino comportara o maximo de horas possivel

        // Separa a parte inteira das horas uteis para cadastrar na hora de termino
        hora.setHora((hora.getHora() + (int) horasUteis) % 24);
        // Separa a parte decimal e tranforma em minutos para cadastrar no minuto de termino
        hora.setMinuto(hora.getMinuto() + (horasUteis - (int) horasUteis) * 60);
        
        // Se os minutos ultrapassarem 60, faz a conversao para hora
        if(hora.getMinuto() >= 60) {
            hora.setHora((hora.getHora() + 1 ) % 24);
            hora.setMinuto(hora.getMinuto() - 60);
        }

        // Cadastra o horario de termino adequado
        ponto.setHorarioTermino(hora);          
    }
    
    // Atualiza o vetor de pontos com o ponto cadastrado   
    this->pontos.push_back(ponto);
}

// Calcula a quantidade de horas trabalhadas pelo funcionario em uma semana
double Funcionario::calculaHorasSemanais(Data data) {

    int semanaAtual = descobreSemana(data);
    double horasTrabalhadas = 0;

    // Varrer o trem ao contrario porque e mais provavel ser a ultima semana
    for(auto element: this->pontos) {
        if(descobreSemana(element.getData()) == semanaAtual)
            horasTrabalhadas += element.calculaHoras();

        else if(descobreSemana(element.getData()) > semanaAtual)
            break;
    }

    return horasTrabalhadas;
}

void Funcionario::exibirSalario() {}
void Funcionario::listarVendas() {}

// Sobrecarga do cout para imprimir os dados do funcionario
ostream& operator <<(ostream& out, const Funcionario& objeto) {
    out << "Nome: " << objeto.getNome() << "\n" <<"Usuário: " << 
        objeto.usuario << "\n" << "Tipo de funcionário: " << 
        objeto.getTipoFuncionario() << "\n" << "Função: " << objeto.getFuncao();
    return out;
}