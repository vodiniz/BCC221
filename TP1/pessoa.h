#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
#include <string>

using namespace std;

class Pessoa {
    string nome;

public:
    Pessoa(string = "");
    virtual ~Pessoa();
    
    void setNome(string);
    string getNome() const;

    friend ostream& operator <<(ostream&, const Pessoa&);
};

#endif