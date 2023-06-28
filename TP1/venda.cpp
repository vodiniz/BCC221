#include <iostream>
#include <iomanip>

#include "venda.h"
#include "data.h"
#include "formatacao.h"

using namespace std;

// Construtor da classe Venda
Venda::Venda(double valor, Data data) {

    // Lança exceção quando o valor da venda é menor ou igual a 0.0
    if(valor <= 0.0) {
        throw out_of_range("\x1b[1m\x1b[31mAs vendas devem ser maiores que R$ 0,00.\n\x1b[0m");
    }

    else {
        setValor(valor);
        this->data = data;
    }
}

// Destrutor da classe Venda
Venda::~Venda() {}

// Setter e getter do valor da venda
void Venda::setValor(double valor) {
    this->valor = valor;
}
double Venda::getValor() const {
    return this->valor;
}

// Setter e getter da data da venda
void Venda::setData(int dia, int mes, int ano){
    this->data.setDia(dia);
    this->data.setMes(mes);
    this->data.setAno(ano);
}
Data Venda::getData() const{
    return this->data;
}

// Sobrecarga do cout para imprimir a data e o valor da venda
ostream &operator <<(ostream &out, const Venda &objeto) {
    out 
    //<< "\t" << AZUL << objeto.data << RESETA << endl
    << "\t\t" << NEGRITO << "Valor da venda: " << RESETA << "R$ " << objeto.valor << endl;
    return out;
}
