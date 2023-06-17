#include <iostream>
#include "ponto.h"

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

    double horasTrabalhadas = 24 - (this->inicio.getHora() + ((60 - this->inicio.getMinuto())) / 60.0) + this->termino.getHora() + (this->termino.getMinuto() / 60.0);

    // Lanca excecao quando o funcionario tenta cadastrar perto de 24 horas
    if(this->inicio.getHora() == this->termino.getHora() && this->inicio.getMinuto() >= this->termino.getMinuto()) {
        //criar exceção nova para melhorar o código.
        throw out_of_range("\033[31mLimite de horas diário excedido. Você não pode trabalhar mais de 10 horas.");
    }
        
    // Saiu no outro dia
    else if(horasTrabalhadas > 10) {
        cout << "horas trabalhadas: " << horasTrabalhadas << "\n";
        //throw out_of_range("\033[31mLimite de horas diário excedido. Você não pode trabalhar mais de 10 horas.");
    }

    return horasTrabalhadas;
}

// Sobrecarga do cout para imprimir a data e os horarios de entrada e saida
ostream& operator <<(ostream& out, const Ponto& objeto) {
    out << "\nDia: "<< objeto.dia << "\nHorário de Entrada: " << objeto.inicio << "\nHorário de Saída: " << objeto.termino;
    return out;
}