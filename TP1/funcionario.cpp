#include <iostream>
#include <iomanip>

#include "pessoa.h"
#include "funcionario.h"
#include "excecao.h"
#include "data.h"

using namespace std;

// Construtor da classe Funcionario
Funcionario::Funcionario(string nome, string usuario, string senha, 
    string tipoFuncionario, string funcao, double salarioPorHora) :
    Pessoa(nome), usuario(usuario), senha(senha), tipoFuncionario(tipoFuncionario),
    funcao(funcao), salarioPorHora(salarioPorHora) {}

// Destrutor da classe Funcionario
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

void Funcionario::setSalarioPorHora(double salarioPorHora){
    this->salarioPorHora = salarioPorHora;
}

double Funcionario::getSalarioPorHora() const{
    return this->salarioPorHora;
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

// GAMBIARRA
double Funcionario::calcularSalario(int mes, int ano) {
    return 0.;
}
void Funcionario::exibirSalario(int mes, int ano) {
    return;
}
void Funcionario:: listarVendas() {
    return;
}

// Calcula a quantidade de horas trabalhadas pelo funcionario em uma semana
double Funcionario::calculaHorasSemanais(Data data) {

    int semanaAtual = descobreSemana(data);
    double horasTrabalhadas = 0;

    // Varre o vetor de pontos
    for(auto element: this->pontos) {

        // Se a semana do ponto analisado for a semana atual, soma as horas 
        if(descobreSemana(element.getData()) == semanaAtual)
            horasTrabalhadas += element.calculaHoras();

        // Se a semana do ponto analisado for maior do que semana atual, para,
        // pois a semana requerida acabou
        else if(descobreSemana(element.getData()) > semanaAtual)
            break;
    }

    return horasTrabalhadas;
}

// Calcula a quantidade de horas trabalhadas pelo funcionario em um mes
double Funcionario::calculaHorasMensais(int mes, int ano) {

    // Lanca execao quando o mes informado esta fora do intervalo correto
    if(mes < 1 || mes > 12) {
        throw out_of_range("\033[31mMeses devem estar entre 1 e 12.\n");
    }

    double horasMensais = 0.;

    // Varre o vetor de pontos
    for(Ponto ponto: this->pontos) {

        // Se o ano do ponto analisado for maior do que o ano requerido, para
        if(ponto.getData().getAno() > ano)
            break;

        // Se o ano do ponto analisado for menor do que o ano requerido, continua
        else if (ponto.getData().getAno() < ano)
            continue;

        // Se o ano do ponto analisado for o ano requerido, soma as horas
        else if(ponto.getData().getMes() == mes && ponto.getData().getAno() == ano)
            horasMensais += ponto.calculaHoras();
    }

    return horasMensais;
}

// Sobrecarga do cout para imprimir os dados do funcionario
ostream& operator <<(ostream &out, const Funcionario &objeto) {
    out << "Nome: " << objeto.getNome() << endl
        << "Usuário: " << objeto.usuario << endl
        << "Tipo de funcionário: " << objeto.getTipoFuncionario() << endl
        << "Função: " << objeto.getFuncao();
    return out;
}