#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "chefe.h"

using namespace std;

enum tipoMenu {INDEFINIDO = 0, CHEFE = 1, SUPERVISOR = 2, FUNCIONARIO = 3};

class Menu{

    Chefe chefe;
    tipoMenu tipoFuncionario = INDEFINIDO;
    
    public:

        Menu(int = 0);
        // Destrutor da classe Menu
        virtual ~Menu();

        void setMenu(int);
        tipoMenu getMenu() const;

        void login();
        void mostrarOpcoes();
        void opcoes();

        // Metodos do chefe

        void cadastrarFuncionario();
        void listarFuncionarios();
        void mostrarPontoFuncionarios();
        void exibirSalarioFuncionarios();

        //Metodos do funcionario

        void cadastrarPonto();
        void exibirSalario();
        void cadastrarVenda();
        void listarVenda();

};

#endif