#include <iostream>
#include <string>

#include "excecao.h"

using namespace std;

// Construtor da classe HorasExcedidas
HorasExcedidas::HorasExcedidas(const string &mensagem, int linha):
    mensagem(mensagem), linha(linha) {}

// Destrutor da classe HorasExcedidas
HorasExcedidas::~HorasExcedidas() {}

// Mostra quando ocorre uma exceção no try
string HorasExcedidas::what() const {
    return this->mensagem;
}

// ---------------------- 

// Construtor da classe UsuarioJaExistente
UsuarioJaExistente::UsuarioJaExistente(const string &mensagem, int linha):
    mensagem(mensagem), linha(linha) {}

// Destrutor da classe UsuarioJaExistente
UsuarioJaExistente::~UsuarioJaExistente() {}

// Mostra quando ocorre uma exceção no try
string UsuarioJaExistente::what() const {
    return this->mensagem;
}

// ----------------------

// Destrutor da classe UsuarioSenhaInvalido
UsuarioSenhaInvalido::UsuarioSenhaInvalido(const string &mensagem, int linha):
    mensagem(mensagem), linha(linha) {}

// Destrutor da classe UsuarioSenhaInvalido
UsuarioSenhaInvalido::~UsuarioSenhaInvalido() {}

// Mostra quando ocorre uma exceção no try
string UsuarioSenhaInvalido::what() const {
    return this->mensagem;
}