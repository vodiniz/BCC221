#include <iostream>

#include "ponto.h"
#include "horario.h"
#include "excecao.h"
#include "formatacao.h"

// Construtor da classe Ponto
Ponto::Ponto(Data dia, Horario inicio, Horario fim) {
    setData(dia);
    setHorarioInicio(inicio);
    setHorarioTermino(fim);
}

// Destrutor da classe Ponto
Ponto::~Ponto() {}

// Setter e getter da data
void  Ponto::setData(Data data) {
    this->dia = data;
}
Data Ponto::getData() const {
    return this->dia;
}

// Setter e getter do horário de início
void Ponto::setHorarioInicio(Horario inicio) {
    this->inicio = inicio;
}
Horario Ponto::getHorarioInicio() const {
    return this->inicio;
}

// Setter e getter do horário de término
void Ponto::setHorarioTermino(Horario termino) {
    this->termino = termino;
}
Horario Ponto::getHorarioTermino() const {
    return this->termino;
}

// Calcula a quantidade de horas trabalhadas pelo funcionário em um dia
double Ponto::calculaHoras() {

    // Calcula a diferença de horas e depois de minutos
    int diferencaHoras = this->getHorarioTermino().getHora() - this->getHorarioInicio().getHora() - 1;
    int diferencaMinutos = this->getHorarioTermino().getMinuto() + (60 - this->getHorarioInicio().getMinuto());

    // Se a diferença de minutos for >= 60,
    // acrescenta 1 nas horas e diminui 60 dos minutos
    if(diferencaMinutos >= 60) {
        diferencaHoras++;
        diferencaMinutos -= 60;
    }

    // Se a diferença entre as horas estiver negativa, o funcionário ficou um dia,
    // então aumenta 24 nas horas
    if(diferencaHoras < 0)
        diferencaHoras += 24;

    // Verifica se o saldo de horas é > 10,
    // ou, se for = 10, se o saldo de minutos é > 0.
    // Caso sim, lança a exceção de horas excedidas.
    if(diferencaHoras > MAXIMO_HORAS_DIARIAS || (diferencaHoras == MAXIMO_HORAS_DIARIAS && diferencaMinutos > 0))
        throw HorasExcedidas("\x1b[1m\x1b[31mLimite de horas diário excedido. Você não pode trabalhar mais do que 10 horas.\x1b[0m", __LINE__);
    
    double horasTrabalhadas = diferencaHoras + diferencaMinutos / 60.0;

    return horasTrabalhadas;
}

// Sobrecarga do cout para imprimir a data e os horários de entrada e saída
ostream &operator <<(ostream &out, const Ponto &objeto) {
    out << CIANO_NEGRITO << "Dia: " << RESETA << objeto.dia << endl
        << "\t" << NEGRITO << "Entrada: " << RESETA << objeto.inicio << endl
        << "\t" << NEGRITO << "Saída: " << RESETA << objeto.termino;
    return out;
}