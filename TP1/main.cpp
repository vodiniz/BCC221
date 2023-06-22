#include <iostream>

#include "data.h"
#include "horario.h"
#include "ponto.h"
#include "chefe.h"
#include "vendedor.h"
#include "supervisor.h"
#include "menu.h"

using namespace std;

void testeFuncoes();

int main() {

    // testeFuncoes();
    Menu menu;
    menu.login();
    
    // cout << "Setteres e getteres" << "Sorveteres" << endl;

    return 0;
}

void testeFuncoes() {
    Chefe kezia("Kezia", "kez", "kez", 35000);
    cout << "Chefe: " << kezia << endl << "-----------" << endl;

    Data data(1, 1, 23);
    cout << data << endl << "-----------" << endl;

    Horario horaA(10, 0), horaB (20, 0);
    cout << horaA << endl << horaB << endl <<  "-----------" << endl;

    Ponto ponto(data, horaA, horaB);
    cout << ponto << endl <<  "-----------" << endl;

    Supervisor jessica("Jessica", "jessica", "presida2023", "supervisor", "Supervisora da presida", 100);
    cout << jessica << endl <<  "-----------" << endl;

    Vendedor bruno("Bruno", "nobru", "probono", "vendedor", "Vendedor de sonhos", 90.);
    cout << bruno << endl <<  "-----------" << endl;

    Venda carro(80000., 1, 1, 2023);
    Venda carro2(180000., 1, 1, 2023);

    // cout << carro << endl <<  "-----------" << endl;

    bruno.cadastrarVenda(carro);
    bruno.cadastrarVenda(carro2);

    bruno.listarVendas();

    cout << "---------------" << endl;

    bruno.exibirSalario(1, 2023);
    cout << endl << "---------------" << endl;


    bruno.cadastrarPonto(Ponto(Data(1,1,2023), horaA, horaB));
    bruno.cadastrarPonto(Ponto(Data(2,1,2023), horaA, horaB));
    bruno.cadastrarPonto(Ponto(Data(3,1,2023), horaA, horaB));
    bruno.cadastrarPonto(Ponto(Data(4,1,2023), horaA, horaB));
    bruno.cadastrarPonto(Ponto(Data(5,1,2023), horaA, horaB));

    bruno.exibirSalario(1,2023);

    cout << endl << "-------JESSICA--------" << endl;

    jessica.adicionarSupervisionado(&bruno);
    // jessica.exibirSalario(1,2023);
    jessica.listarVendas();
    cout << endl << "---------------" << endl;

    cout << endl << "-------KÉZIA--------" << endl;

    kezia.exibeSalario();
    cout << endl;
    kezia.cadastrarFuncionario(&jessica);
    kezia.cadastrarFuncionario(&bruno);

    kezia.listarFuncionarios();
    
    cout << endl << "---------------" << endl;
    
    kezia.checarPonto(1, 2023);

    cout << endl << " ---------------" << endl;
    cout << endl << "---------------" << endl;
    kezia.calcularSalario(1,2023);
    cout << endl << "  keziaaaaaaaaaaaaaaaa---------------" << endl;
    cout << kezia;
}