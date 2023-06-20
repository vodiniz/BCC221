#ifndef DATA_H
#define DATA_H

#include <iostream>

using namespace std;

class Data {
    int dia;
    int mes;
    int ano;

public:
    Data(int = 1, int = 1, int = 2023);
    virtual ~Data();

    void setDia(int dia);
    int getDia() const;

    void setMes(int mes);
    int getMes() const;
    
    void setAno(int ano);
    int getAno() const;

    friend int descobreSemana(Data);
    friend ostream& operator <<(ostream&, const Data&);
};

#endif