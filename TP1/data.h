#ifndef DATA_H
#define DATA_H

#include <iostream>

#include "formatacao.h"

using namespace std;

/* // Guarda os meses referentes aos seus números
char *nomeMes(int m) {
    switch (m) {
        case 1:
            return "Janeiro";
            break;
        case 2:
            return "Fevereiro";
            break;
        case 3:
            return "Março";
            break;
        case 4:
            return "Abril";
            break;
        case 5:
            return "Maio";
            break;
        case 6:
            return "Junho";
            break;
        case 7:
            return "Julho";
            break;
        case 8:
            return "Agosto";
            break;
        case 9:
            return "Setembro";
            break;
        case 10:
            return "Outubro";
            break;
        case 11:
            return "Novembro";
            break;
        case 12:
            return "Dezembro";
            break;
        default:
            return "Mês inválido";
    }
} */

// Classe Data
// Base
class Data {
    int dia;
    int mes;
    int ano;

public:
    // Construtor da classe Data
    Data(int = 1, int = 1, int = 2023);
    // Destrutor da classe Data
    virtual ~Data();

    // Setter e getter do dia
    void setDia(int dia);
    int getDia() const;

    // Setter e getter do mês
    void setMes(int mes);
    int getMes() const;
    
    // Setter e getter do ano
    void setAno(int ano);
    int getAno() const;

    // Descobre o número da semana
    friend int descobreSemana(Data);
    // Sobrecarga do cout para imprimir a data
    friend ostream &operator <<(ostream&, const Data&);
};

#endif