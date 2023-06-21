#include <iostream>
#include <iomanip>

#include "menu.h"
#include "chefe.h"

using namespace std;

// Construtor da classe Menu
Menu::Menu(int tipoFuncionario) {
    this->chefe = Chefe("bruno", "admin", "admin", 100000);
    this->tipoFuncionario = static_cast<tipoMenu>(tipoFuncionario);
}

// Destrutor da classe Menu
Menu::~Menu() {}


void Menu::setMenu(int tipoFuncionario){
    this->tipoFuncionario = static_cast<tipoMenu>(tipoFuncionario);
}

tipoMenu Menu::getMenu() const{
    return this->tipoFuncionario;
}

