#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

class HorasExcedidas {
    string mensagem;
    int linha;

public:
    HorasExcedidas(const string& mensagem, int linha);
    ~HorasExcedidas();

    string what() const;
};

#endif