#include <iostream>
#include <string>

#include "excecao.h"

using namespace std;

// Construtor da classe HorasExcedidas
HorasExcedidas::HorasExcedidas(const string &mensagem, int linha):
    mensagem(mensagem), linha(linha) {}

// Destrutor da classe HorasExcedidas
HorasExcedidas::~HorasExcedidas() {}

// Quando ocorre uma excecao no try, indica o erro e a linha onde ocorreu
string HorasExcedidas::what() const {
    return this->mensagem + " na linha " + to_string(this->linha);
}

// ----------------------

// Construtor da classe UsuarioJaExistente
UsuarioJaExistente::UsuarioJaExistente(const string &mensagem, int linha):
    mensagem(mensagem), linha(linha) {}

// Destrutor da classe UsuarioJaExistente
UsuarioJaExistente::~UsuarioJaExistente() {}

// Quando ocorre uma excecao no try, indica o erro e a linha onde ocorreu
string UsuarioJaExistente::what() const {
    return this->mensagem + " na linha " + to_string(this->linha);
}


UsuarioSenhaInvalido::UsuarioSenhaInvalido(const string &mensagem, int linha):
    mensagem(mensagem), linha(linha) {}

// Destrutor da classe UsuarioJaExistente
UsuarioSenhaInvalido::~UsuarioSenhaInvalido() {}

// Quando ocorre uma excecao no try, indica o erro e a linha onde ocorreu
string UsuarioSenhaInvalido::what() const {
    return this->mensagem;
}