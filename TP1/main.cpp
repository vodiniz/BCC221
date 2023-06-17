#include <iostream>

#include "data.h"
#include "horario.h"
#include "ponto.h"

using namespace std;

int main() {
    // cout << "Setteres e getteres" << "Sorveteres" << endl;

    Horario x(22, 10);
    Horario y(22, 20);
    Data z(10, 1);
    Ponto ponto(z, x, y);

    cout << "Horas trabalhadas: " << ponto.calculaHoras() << endl;

    return 0;    
}