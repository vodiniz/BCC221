#include <iostream>
#include <string>

#include "excecao.h"

using namespace std;

// Construtor da classe HorasExcedidas
HorasExcedidas::HorasExcedidas(const string& mensagem, int linha):
    mensagem(mensagem), linha(linha) {}

// Destrutor da classe HorasExcedidas
HorasExcedidas::~HorasExcedidas() {}

// Mostra o erro e em qual linha ele ocorreu
string HorasExcedidas::what() const {
    return this->mensagem + " na linha " + to_string(this->linha);
}