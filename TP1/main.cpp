#include <iostream>

#include "data.h"
#include "horario.h"
#include "ponto.h"
#include "chefe.h"
#include "vendedor.h"

using namespace std;

int main() {
    // cout << "Setteres e getteres" << "Sorveteres" << endl;

    Horario x(10, 0);
    Horario y(18, 0);
    Data z(18, 6);
    Ponto ponto(z, x, y);

    Venda carro(40000.);
    Venda carro2(4000.1);

    
    Chefe chefinho("Poderoso");

    Vendedor vendedor("Chaves", "chavinho", "seninha", "Vendedor", "Vendo produtos", 0.0);

    vendedor.cadastrarVenda(carro);
    vendedor.cadastrarVenda(carro2);



    cout << vendedor << vendedor.calcularVendas() << endl;

    vendedor.listarVendas();

    return 0;    
}