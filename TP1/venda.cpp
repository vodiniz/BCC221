#include <iostream>
#include <iomanip>

#include "venda.h"

using namespace std;

// Construtor da classe Venda
Venda::Venda(double valor) {

    // Lanca excecao quando o valor da venda e menor ou igual a 0.0
    if(valor <= 0.0) {
        throw out_of_range("\033[31mAs vendas devem ser maiores do que R$ 0,00.\n");
    }

    else {
        setValor(valor);
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

// Sobrecarga do cout para imprimir o valor da venda
ostream& operator <<(ostream& out, const Venda& objeto) {
    // Aqui usamos o setprecision para imprimir o valor com duas casas decimais
    out << "Valor da venda: R$ " << setprecision(2) << objeto.valor;
    return out;
}