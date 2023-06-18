#include <iostream>

#include "data.h"
#include "horario.h"
#include "ponto.h"

using namespace std;

int main() {
    // cout << "Setteres e getteres" << "Sorveteres" << endl;

    Horario x(23, 10);
    Horario y(23, 5);
    Data z(18, 6);
    Ponto ponto(z, x, y);

    // cout << descobreSemana(ponto.getData) << endl;

    return 0;    
}