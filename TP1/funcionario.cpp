#include <iostream>
#include <iomanip>

#include "pessoa.h"
#include "funcionario.h"
#include "excecao.h"
#include "data.h"
#include "formatacao.h"

using namespace std;

// Construtor da classe Funcionario
Funcionario::Funcionario(string nome, string usuario, string senha, 
    string tipoFuncionario, string funcao, double salarioPorHora) :
    Pessoa(nome), usuario(usuario), senha(senha), tipoFuncionario(tipoFuncionario),
    funcao(funcao), salarioPorHora(salarioPorHora) {}

// Destrutor da classe Funcionario
Funcionario::~Funcionario() {
    this->liberaPontos();
}

// Setter e getter do usuário
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

// Setter e getter do tipo de funcionário
void Funcionario::setTipoFuncionario(string tipoFuncionario) {
    this->tipoFuncionario = tipoFuncionario;
}
string Funcionario::getTipoFuncionario() const {
    return this->tipoFuncionario;
}

// Setter e getter da função
void Funcionario::setFuncao(string funcao) {
    this->funcao = funcao;
}
string Funcionario::getFuncao() const {
    return this->funcao;
}

// Setter e getter do salário
void Funcionario::setSalarioPorHora(double salarioPorHora){
    this->salarioPorHora = salarioPorHora;
}
double Funcionario::getSalarioPorHora() const{
    return this->salarioPorHora;
}

// Cadastra o ponto diário do funcionário
void Funcionario::cadastrarPonto(Ponto *ponto) {
    
    double horasSemanais = calculaHorasSemanais(ponto->getData());
    double horasUteis;
    
    // Impede o funcionário de cadastrar um ponto se já tiver chegado ao limite
    if(horasSemanais >= MAXIMO_HORAS_SEMANAIS)
        throw HorasExcedidas("\x1b[1m\x1b[31mVocê já trabalhou 50 horas essa semana.\x1b[0m", __LINE__);

    // Caso o funcionário tente cadastrar um ponto que ultrapasse o limite,
    // cadastra o máximo de tempo que pode sem estourar.
    else if(horasSemanais + ponto->calculaHoras() > MAXIMO_HORAS_SEMANAIS) {
        
        horasUteis = MAXIMO_HORAS_SEMANAIS - horasSemanais; // máximo de horas que podem ser cadastradas
        Horario hora = ponto->getHorarioInicio();
        
        // O horário de início do ponto não será alterado
        // O horário de término comportará o máximo de horas possível

        // Separa a parte inteira das horas úteis para cadastrar na hora de término
        hora.setHora((hora.getHora() + (int) horasUteis) % 24);
        // Separa a parte decimal e tranforma em minutos para cadastrar no minuto de término
        hora.setMinuto(hora.getMinuto() + (horasUteis - (int) horasUteis) * 60);
        
        // Se os minutos ultrapassarem 60, faz a conversão para hora
        if(hora.getMinuto() >= 60) {
            hora.setHora((hora.getHora() + 1 ) % 24);
            hora.setMinuto(hora.getMinuto() - 60);
        }

        // Cadastra o horário de término adequado
        ponto->setHorarioTermino(hora);          
    }
    // Atualiza o vetor de pontos com o ponto cadastrado   
    this->pontos.push_back(ponto);
}

// Libera os pontos que são referenciados pelo vector
void Funcionario::liberaPontos(){

    for(Ponto* ponto : this->pontos)
        delete ponto;

}

double Funcionario::calcularSalario(int mes, int ano) {
    return 0.;
}
void Funcionario::exibirSalario(int mes, int ano) {
    return;
}
void Funcionario::listarVendas() {
    return;
}

// Calcula a quantidade de horas trabalhadas pelo funcionário em uma semana
double Funcionario::calculaHorasSemanais(Data data) {

    int semanaAtual = descobreSemana(data);
    int semanaPonto;
    double horasTrabalhadas = 0;

    // Varre o vetor de pontos
    for(auto pPonto: this->pontos) {

        semanaPonto = descobreSemana(pPonto->getData());

        // Se a semana do ponto analisado for a semana atual, soma as horas 
        if(semanaPonto == semanaAtual)
            horasTrabalhadas += pPonto->calculaHoras();

        // Se a semana do ponto analisado for maior do que semana atual, para,
        // pois a semana requerida acabou
        else if(semanaPonto > semanaAtual)
            break;
    }

    return horasTrabalhadas;
}

// Calcula a quantidade de horas trabalhadas pelo funcionário em um mês
double Funcionario::calculaHorasMensais(int mes, int ano) {

    // Lança exceção quando o mês informado está fora do intervalo correto
    if(mes < 1 || mes > 12) {
        throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
    }

    double horasMensais = 0.;

    // Varre o vetor de pontos
    for(Ponto *pPonto: this->pontos) {

        // Se o ano do ponto analisado for maior do que o ano requerido, para
        if(pPonto->getData().getAno() > ano)
            break;

        // Se o ano do ponto analisado for menor do que o ano requerido, continua
        else if (pPonto->getData().getAno() < ano)
            continue;

        // Se o ano do ponto analisado for o ano requerido, soma as horas
        else if(pPonto->getData().getMes() == mes && pPonto->getData().getAno() == ano)
            horasMensais += pPonto->calculaHoras();
    }

    return horasMensais;
}

// Sobrecarga do cout para imprimir os dados do funcionário
ostream &operator <<(ostream &out, const Funcionario &objeto) {
    out << CIANO_NEGRITO << objeto.getNome() << RESETA << endl
        << "\t" << NEGRITO << "Usuário: " << RESETA << objeto.usuario << endl
        << "\t" << NEGRITO << "Tipo de funcionário: " << RESETA << objeto.getTipoFuncionario() << endl
        << "\t" << NEGRITO << "Função: " << RESETA << objeto.getFuncao();
    return out;
}