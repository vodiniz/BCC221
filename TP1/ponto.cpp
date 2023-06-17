#include <iostream>

#include "ponto.h"
#include "horario.h"
#include "exception.h"

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

double Ponto::calculaHoras() {

    int diferencaHoras = this->getHorarioTermino().getHora() - this->getHorarioInicio().getHora() - 1;
    int diferencaMinutos = this->getHorarioTermino().getMinuto() + (60 - this->getHorarioInicio().getMinuto());

    if (diferencaMinutos >= 60){
        diferencaHoras++;
        diferencaMinutos -= 60;
    }

    if(diferencaHoras < 0)
        diferencaHoras += 24;

    if(diferencaHoras > 10 || (diferencaHoras == 10 && diferencaMinutos > 0))
        throw HorasExcedidas("\033[31mLimite de horas diário excedido. Você não pode trabalhar mais de 10 horas.", __LINE__);
    
    double horasTrabalhadas = diferencaHoras + diferencaMinutos / 60.0;


    return horasTrabalhadas;
}

// Sobrecarga do cout para imprimir a data e os horarios de entrada e saida
ostream& operator <<(ostream& out, const Ponto& objeto) {
    out << "\nDia: "<< objeto.dia << "\nHorário de Entrada: " << objeto.inicio << "\nHorário de Saída: " << objeto.termino;
    return out;
}