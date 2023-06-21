#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

// Classe HorasExcedidas
// Base
class HorasExcedidas {
    string mensagem;
    int linha;

public:
    // Construtor da classe HorasExcedidas
    HorasExcedidas(const string &mensagem, int linha);
    // Destrutor da classe HorasExcedidas
    virtual ~HorasExcedidas();

    // Quando ocorre uma excecao no try, indica o erro e a linha onde ocorreu
    string what() const;
};

// --------------------

class UsuarioJaExistente {
    string mensagem;
    int linha;

public:
    // Construtor da classe UsuarioJaExistente
    UsuarioJaExistente(const string &mensagem, int linha);
    // Destrutor da classe UsuarioJaExistente
    virtual ~UsuarioJaExistente();

    // Quando ocorre uma excecao no try, indica o erro e a linha onde ocorreu
    string what() const;
};

#endif