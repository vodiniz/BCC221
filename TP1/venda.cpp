#include <iostream>
#include <iomanip>

#include "venda.h"

using namespace std;

// Construtor da classe Venda
Venda::Venda(double valor, int dia, int mes, int ano) {

    // Lanca excecao quando o valor da venda eh menor ou igual a 0.0
    if(valor <= 0.0) {
        throw out_of_range("\033[31mAs vendas devem ser maiores que R$ 0,00.\n");
    }

    else {
        setValor(valor);
        this->data = Data(dia, mes, ano);
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
ostream& operator <<(ostream &out, const Venda &objeto) {
    out << objeto.data << endl
        << "\t" << "Valor da venda: R$ " << objeto.valor;
    return out;
}