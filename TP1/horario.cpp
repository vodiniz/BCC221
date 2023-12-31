#include <iostream>
#include <iomanip>

#include "horario.h"

using namespace std;

// Construtor da classe Horario
Horario::Horario(int hora, int minuto) {
    
    // Lança exceção quando a hora informada está fora do intervalo correto
    if(hora < 0 || hora > 23) {
        throw out_of_range("\x1b[1m\x1b[31mHoras devem estar entre 0 e 23.\n\x1b[0m");
    }

    // Lança exceção quando o minuto informado está fora do intervalo correto
    else if(minuto < 0 || minuto > 59) {
        throw out_of_range("\x1b[1m\x1b[31mMinutos devem estar entre 0 e 59.\n\x1b[0m");
    }
    
    else {
        setHora(hora);
        setMinuto(minuto);
    }
}

// Destrutor da classe Horario
Horario::~Horario() {}

// Setter e getter da hora
void Horario::setHora(int hora) {
    this->hora = hora;
}
int Horario::getHora() const {
    return this->hora;
}

// Setter e getter do minuto
void Horario::setMinuto(int minuto) {
    this->minuto = minuto;
}
int Horario::getMinuto() const {
    return this->minuto;
}

// Sobrecarga do cout para imprimir o horário
ostream &operator <<(ostream &out, const Horario &objeto) {
    // Aqui usamos setw para padronizar a impressão como DD/MM/AAAA
    // e setfill para preencher com 0 pela esquerda
    out << setw(2) << setfill('0') << objeto.hora << ":" << setw(2) << setfill('0') << objeto.minuto;
    return out;
}