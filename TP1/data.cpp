#include <iostream>
#include <iomanip>

#include "data.h"
#include "formatacao.h"

using namespace std;

// Construtor da classe Data
Data::Data(int dia, int mes, int ano) {

    // Lança exceção quando o dia informado está fora do intervalo correto
    // OLHAR MÊS A MÊS
    if(dia < 1 || dia > 31) {
        throw out_of_range("\x1b[1m\x1b[31mDias devem estar entre 1 e 31.\n\x1b[0m");
    }

    // Lança exceção quando o mês informado está fora do intervalo correto
    else if(mes < 1 || mes > 12) {
        throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
    }

    else {
        setDia(dia);
        setMes(mes);
        setAno(ano);
    }
}

// Destrutor da classe Data
Data::~Data() {}

// Setter e getter do dia
void Data::setDia(int dia) {
    this->dia = dia;
}
int Data::getDia() const {
    return this->dia;
}

// Setter e getter do mês
void Data::setMes(int mes) {
    this->mes = mes;
}
int Data::getMes() const {
    return this->mes;
}

// Setter e getter do ano
void Data::setAno(int ano) {
    this->ano = ano;
}
int Data::getAno() const {
    return this->ano;
}

// Descobre o número da semana
// Auxilia a saber quando vira de uma semana para a outra
int descobreSemana(Data data) {

    int dia = data.getDia();
    int mes = data.getMes();
    int ano = data.getAno();

    int numeroSemana = (dia+= mes < 3 ? ano-- : ano - 2, 23 * mes / 9 + dia + 4 + ano/4 - ano/100 + ano/400) / 7;
        
    return numeroSemana;   
}

// Sobrecarga do cout para imprimir a data
ostream &operator <<(ostream &out, const Data &objeto) {
    // Aqui usamos setw para padronizar a impressão como DD/MM/AAAA
    // e setfill para preencher com 0 pela esquerda
    out << setw(2) << setfill('0') << objeto.dia << "/" << setw(2) << setfill('0') << objeto.mes << "/" << objeto.ano;
    return out;
}