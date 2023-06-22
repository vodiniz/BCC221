#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <exception>
#include <limits>

#include "menu.h"
#include "chefe.h"
#include "excecao.h"
#include "formatacao.h"

using namespace std;

// Construtor da classe Menu
Menu::Menu(int tipoFuncionario) {
    this->chefe = Chefe("Bruno", "admin", "admin", 100000);
    this->funcionario = NULL;
    this->tipoFuncionario = static_cast<tipoMenu>(tipoFuncionario);
}

// Destrutor da classe Menu
Menu::~Menu() {}

// Setter e getter do menu
void Menu::setMenu(int tipoFuncionario) {
    this->tipoFuncionario = static_cast<tipoMenu>(tipoFuncionario);
}
tipoMenu Menu::getMenu() const {
    return this->tipoFuncionario;
}

// Checa se as informações de login batem com algum usuario existente
bool Menu::checaLogin(string usuario, string senha) {
    
    // Se as informacoes de login forem iguais as do chefe, seta o menu do chefe
    if(this->chefe.getUsuario() == usuario && this->chefe.getSenha() == senha) {
        this->setMenu(1);
        return true;
    }

    // Senao, checa se as informacoes de login equivalem as de algum funcionario
    else {
        for(auto funcionario: this->chefe.getFuncionarios()) {
            if(funcionario.getUsuario() == usuario && funcionario.getSenha() == senha) {
                // Se bater com as informacoes de login de um supervisor, seta o menu do supervisor
                if(funcionario.getTipoFuncionario() == "Supervisor")
                    this->setMenu(2);
                // Se bater com as informacoes de login de um vendedor, seta o menu do vendedor
                else if(funcionario.getTipoFuncionario() == "Vendedor")
                    this->setMenu(3);
                
                this->funcionario = &funcionario;
                return true;
            }
        }
    }
    
    return false;
}

// Loop para o login e logout
void Menu::login() {

    string usuario, senha;
    
    // Loop que pede o login enquanto um login invalido eh informado
    while(true) {
        try {
            cout << "\x1b[1m\x1b[32mFaça o login ou digite -1 para sair.\x1b[0m" << "\n" << endl;
            
            // Recebe o usuario
            cout << "\x1b[1m\x1b[34mUsuário:\x1b[0m ";
            cin >> usuario;

            // Se receber um -1, o programa encerra
            if(usuario == "-1") {
                cout << "\x1b[1m\x1b[32m\nLogout efetuado com sucesso! Até a próxima :(\x1b[0m" << endl;
                break;
            }
            
            // Recebe a senha
            cout << "\x1b[1m\x1b[34mSenha:\x1b[0m ";
            cin >> senha;
            cout << endl;
            
            // Confere se as informacoes de login estao corretas
            // Se sim, realiza o login
            if(checaLogin(usuario, senha)) {
                cout << "\x1b[1m\x1b[32mLogin efetuado com sucesso! Seja bem vindo :)\x1b[0m" << "\n" << endl;
                this->opcoes();
            }
            
            // Senao, informa que o usuario ou a senha estao invalidos
            // e o loop volta no inicio
            else {
                throw UsuarioSenhaInvalido("\x1b[1m\x1b[31mUsuário e/ou senha inválidos.\x1b[0m", __LINE__);
                cout << "\n" << endl; 
            }
        }
        
        // Pega uma exceção polimórfica caso haja algum erro no bloco do try, implementada com foco em um valor inválido no terminal
        catch(exception &e) {
            e.what();
            cout << "\x1b[1m\x1b[31mErro! Digite um valor válido.\x1b[0m" << endl;
        }
        // Pega a exceção UsuarioSenhaInvalida, que foi criada por nós, caso não seja encontrado nenhum usuario cadastrado com os valores informados
        catch(UsuarioSenhaInvalido& e) {
            cout << "\x1b[1m\x1b[31mError\x1b[0m" << e.what() << endl;
        }
    }
}

// Lista as opcoes
void Menu::mostrarOpcoes() {
    
    // Mostra as opcoes do menu do chefe
    if(this->getMenu() == 1) {
        cout << "1 - Cadastrar funcionário." << endl;
        cout << "2 - Listar funcionários." << endl;
        cout << "3 - Mostrar ponto dos funcionários." << endl;
        cout << "4 - Exbir salário dos funcionários." << endl;
        cout << "5 - Voltar." << endl;
    }
    
    // Mostra as opcoes do menu do funcionario
    else {
        cout << "1 - Cadastrar ponto." << endl;
        cout << "2 - Exibir salário." << endl;
        cout << "3 - Listar vendas." << endl;
        // Se for um supervisor, pula para o voltar
        if(this->getMenu() == 2)
            cout << "4 - Voltar." << endl;
        // Se for um vendedor, mostra o cadastrar venda antes do voltar
        else {
            cout << "4 - Cadastrar vendas." << endl;
            cout << "5 - Voltar." << endl;
        }
    }
}

// Loop para selecionar as opcoes e voltar para o menu
void Menu::opcoes() {

    int opcao;

    while(true) {
        
        this->mostrarOpcoes();

        try {
            // Valida o valor, retornando erro se nao for um inteiro
            if(!(cin >> opcao)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
                throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
            }
            
            // Valida a opcao, retornando erro se for invalida
            if(opcao < 1 || ( (this->getMenu() == 2) && (opcao > 4)) || ((this->getMenu() == 3) && (opcao > 5)) || ((this->getMenu() == 1) && (opcao > 5))) {
                throw invalid_argument("\x1b[1m\x1b[31mInsira somente a opção desejada.\n\x1b[0m");
            }
            
            // Opcoes para o chefe
            if(this->getMenu() == 1) {
                switch(opcao) {
                    case 1:
                        this->cadastrarFuncionario();
                        break;

                    case 2:
                        this->listarFuncionarios();
                        break;

                    case 3:
                        this->mostrarPontoFuncionarios();
                        break;

                    case 4:
                        this->exibirSalarioFuncionarios();
                        break;

                    case 5:
                        return;
                        break;
                }
            }

            // Opcoes para o supervisor
            else if(this->getMenu() == 2) {                
                switch(opcao) {
                    case 1:
                        this->cadastrarPonto();
                        break;

                    case 2:
                        this->exibirSalario();
                        break;

                    case 3:
                        this->listarVenda();
                        break;

                    case 4:
                        return;
                        break;
                }
            }

            // Opcoes para o vendedor
            else {
                switch(opcao) {
                    case 1:
                        this->cadastrarPonto();
                        break;

                    case 2:
                        this->exibirSalario();
                        break;

                    case 3:
                        this->listarVenda();
                        break;
                    case 4:

                        this->cadastrarVenda();
                        break;
                        
                    case 5:
                        return;
                        break;
                }
            }
        }
        
        // Retorna o erro que ocorreu no try
        catch(invalid_argument &e) {
            cerr << "\n Erro: " << e.what() << endl;
        }
    }
}

void Menu::cadastrarFuncionario() {}
void Menu::listarFuncionarios() {}
void Menu::mostrarPontoFuncionarios() {}
void Menu::exibirSalarioFuncionarios() {}


void Menu::cadastrarPonto() {}
void Menu::exibirSalario() {}
void Menu::cadastrarVenda() {}
void Menu::listarVenda() {}