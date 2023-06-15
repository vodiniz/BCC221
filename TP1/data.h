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
    ~Data();

    void setDia(int dia);
    void getDia() const;

    void setMes(int mes);
    void getMes() const;
    
    void setAno(int ano);
    void getAno() const;

    friend ostream& operator <<(ostream&, const Data&);
};

#endif