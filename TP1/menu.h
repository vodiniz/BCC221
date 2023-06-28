#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "chefe.h"
#include "funcionario.h"
#include "formatacao.h"


using namespace std;

// Define o nível de acesso ao menu de acordo com o cargo
enum tipoMenu {INDEFINIDO = 0, CHEFE = 1, SUPERVISOR = 2, VENDEDOR = 3};

// Classe Menu
// Base
class Menu {
    Chefe chefe;
    Funcionario *funcionario;
    tipoMenu tipoFuncionario = INDEFINIDO;
    
public:
    // Construtor da classe Menu
    Menu(int = 0);
    // Destrutor da classe Menu
    virtual ~Menu();

    // Setter e getter do menu
    void setMenu(int);
    tipoMenu getMenu() const;
    
    // Checa se as informações de login batem com algum usuário existente
    bool checaLogin(string, string);
    // Loop para o login e logout
    void login();
    // Lista as opções
    void mostrarOpcoes();
    // Loop para selecionar as opções e voltar para o menu
    void opcoes(); 

    // -------------------- Métodos do chefe

    void cadastrarFuncionario();
    void listarFuncionarios();
    void mostrarPontoFuncionarios();
    void calcularSalarioFuncionarios();

    // -------------------- Métodos do funcionário
    
    void cadastrarPonto();
    void exibirSalario();
    void cadastrarVenda(); // apenas o vendedor possui esse método
    void listarVenda();

    // Limpa a tela do terminal
    void limpaTela();
};

#endif