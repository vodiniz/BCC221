#include <iostream>

#include "ponto.h"
#include "horario.h"
#include "excecao.h"

// Construtor da classe Ponto
Ponto::Ponto(Data dia, Horario inicio, Horario fim) {
    setData(dia);
    setHorarioInicio(inicio);
    setHorarioTermino(fim);
}

// Destrutor da classe Ponto
Ponto::~Ponto() {};

// Setter e getter da data
void  Ponto::setData(Data data) {
    this->dia = data;
}
Data Ponto::getData() const {
    return this->dia;
}

// Setter e getter do horario de inicio
void Ponto::setHorarioInicio(Horario inicio) {
    this->inicio = inicio;
}
Horario Ponto::getHorarioInicio() const {
    return this->inicio;
}

// Setter e getter do horario de termino
void Ponto::setHorarioTermino(Horario termino) {
    this->termino = termino;
}
Horario Ponto::getHorarioTermino() const {
    return this->termino;
}

// Calcula a quantidade de horas trabalhadas pelo funcionario em um dia
double Ponto::calculaHoras() {

    // Calcula a diferenca de horas e depois de minutos
    int diferencaHoras = this->getHorarioTermino().getHora() - this->getHorarioInicio().getHora() - 1;
    int diferencaMinutos = this->getHorarioTermino().getMinuto() + (60 - this->getHorarioInicio().getMinuto());

    // Se a diferenca de minutos for >= 60,
    // acrescenta 1 nas horas e diminui 60 dos minutos
    if(diferencaMinutos >= 60) {
        diferencaHoras++;
        diferencaMinutos -= 60;
    }

    // Se a diferenca entre as horas estiver negativa, o funcionario ficou um dia,
    // entao aumenta 24 nas horas
    if(diferencaHoras < 0)
        diferencaHoras += 24;

    // Verifica se o saldo de horas e > 10,
    // ou, se for = 10, se o saldo de minutos e > 0.
    // Caso sim, lanca a excecao de horas excedidas.
    if(diferencaHoras > 10 || (diferencaHoras == 10 && diferencaMinutos > 0))
        throw HorasExcedidas("\033[31mLimite de horas diário excedido. Você não pode trabalhar mais do que 10 horas.", __LINE__);
    
    double horasTrabalhadas = diferencaHoras + diferencaMinutos / 60.0;

    return horasTrabalhadas;
}


// Sobrecarga do cout para imprimir a data e os horarios de entrada e saida
ostream& operator <<(ostream& out, const Ponto& objeto) {
    out << "\nDia: "<< objeto.dia << "\nHorário de Entrada: " << objeto.inicio << "\nHorário de Saída: " << objeto.termino;
    return out;
}