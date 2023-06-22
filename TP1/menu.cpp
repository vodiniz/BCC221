#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <exception>
#include <limits>

#include "menu.h"
#include "chefe.h"
#include "funcionario.h"
#include "supervisor.h"
#include "vendedor.h"
#include "ponto.h"
#include "excecao.h"
#include "formatacao.h"

using namespace std;

// Construtor da classe Menu
Menu::Menu(int tipoFuncionario) {
    this->chefe = Chefe("Bruno", "admin", "admin", 100000);
    this->funcionario = NULL;
    this->tipoFuncionario = static_cast<tipoMenu>(tipoFuncionario);
    
    Funcionario A = Supervisor("a", "a", "a", "Supervisor", "supervisiona", 1000.);
    this->chefe.cadastrarFuncionario(&A);
    
}

// Destrutor da classe Menu
Menu::~Menu() {}

// Setter e getter do menu
void Menu::setMenu(int tipoFuncionario) {
    this->tipoFuncionario = static_cast<tipoMenu>(tipoFuncionario);
    // this->chefe.cadastrarFuncionario();
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
                limpaTela();
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
                limpaTela();
                cout << "\x1b[1m\x1b[32mLogin efetuado com sucesso! Seja bem vindo :)\x1b[0m" << "\n" << endl;
                this->opcoes();
            }
            
            // Senao, informa que o usuario ou a senha estao invalidos
            // e o loop volta no inicio
            else {
                limpaTela();
                throw UsuarioSenhaInvalido("\x1b[1m\x1b[31mUsuário e/ou senha inválidos.\n\x1b[0m", __LINE__);
                cout << "\n" << endl; 
            }
        }
        
        // Pega uma exceção polimórfica caso haja algum erro no bloco do try, implementada com foco em um valor inválido no terminal
        catch(exception &e) {
            limpaTela();
            e.what();
            cout << "\x1b[1m\x1b[31mErro: Digite um valor válido.\x1b[0m" << endl;
        }
        // Pega a exceção UsuarioSenhaInvalida, que foi criada por nós, caso não seja encontrado nenhum usuario cadastrado com os valores informados
        catch(UsuarioSenhaInvalido& e) {
            limpaTela();
            cout << "\x1b[1m\x1b[31mErro:\x1b[0m " << e.what() << endl;
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
        cout << "0 - Voltar.\n" << endl;
    }
    
    // Mostra as opcoes do menu do funcionario
    else {
        cout << "1 - Cadastrar ponto." << endl;
        cout << "2 - Exibir salário." << endl;
        cout << "3 - Listar vendas." << endl;
        // Se for um vendedor, mostra o cadastrar venda antes do voltar
        if(this->getMenu() == 3)
            cout << "4 - Cadastrar vendas." << endl;
        cout << "0 - Voltar.\n" << endl;
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
                limpaTela();
                throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
            }
            
            // Valida a opcao, retornando erro se for invalida
            if(opcao < 0 || ( (this->getMenu() == 2) && (opcao > 3)) || ((this->getMenu() == 3) && (opcao > 5)) || ((this->getMenu() == 1) && (opcao > 5))) {
                limpaTela();
                throw invalid_argument("\x1b[1m\x1b[31mInsira somente a opção desejada.\n\x1b[0m");
            }

            cout << endl;
            limpaTela();
            
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
                        this->calcularSalarioFuncionarios();
                        break;

                    case 0:
                        return;
                        break;
                }
            }

            // Opcoes para o funcionario
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
                    
                    case 0:
                        return;
                        break;
                }
            }
        }
        
        // Retorna o erro que ocorreu no try
        catch(invalid_argument &e) {
            cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
        }
    }
}

// -------------------- Metodos do chefe

void Menu::cadastrarFuncionario() {
    
    string nome, usuario, senha, tipoFuncionario, funcao;
    double salarioPorHora;

    cout << "\x1b[1m\x1b[32mCADASTRO DE FUNCIONÁRIO\x1b[0m\n" << endl;

    // Pega as informações do novo funcionário
    try {
        cout << "\x1b[1mNome:\x1b[0m ";

        cin >> nome;

        cout << "\x1b[1mUsuário:\x1b[0m ";
        cin >> usuario;

        cout << "\x1b[1mSenha:\x1b[0m ";
        cin >> senha;

        cout << "\x1b[1mTipo de funcionário:\x1b[0m ";
        cin >> tipoFuncionario;

        if(!(tipoFuncionario == "Supervisor" || tipoFuncionario == "Vendedor")) {
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mErro: Tipo de funcionário deve ser \"Supervisor\" ou \"Vendedor\".\n\x1b[0m");
        }
        
        cout << "\x1b[1mFunção:\x1b[0m ";
        cin >> funcao;

        cout << "\x1b[1mSalário por hora:\x1b[0m ";

        if(!(cin >> salarioPorHora)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Cadastra o funcionário com a classe correspondente
        
        if(tipoFuncionario == "Supervisor") {
            Funcionario novoFuncionario = Supervisor(nome, usuario, senha, tipoFuncionario, funcao, salarioPorHora);
            this->chefe.cadastrarFuncionario(&novoFuncionario);
        }

        else {
            Funcionario novoFuncionario = Vendedor(nome, usuario, senha, tipoFuncionario, funcao, salarioPorHora);
            this->chefe.cadastrarFuncionario(&novoFuncionario);
        }

        limpaTela();
        cout << "\n\x1b[1m\x1b[32mNovo funcionário cadastrado com sucesso!\x1b[0m\n" << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna erro quando o usuário já existe
    catch(UsuarioJaExistente &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }
}

void Menu::listarFuncionarios() {
    cout << "\x1b[1m\x1b[32mFUNCIONÁRIOS CADASTRADOS\x1b[0m\n" << endl;
    this->chefe.listarFuncionarios();
}

void Menu::mostrarPontoFuncionarios() {

    cout << "\x1b[1m\x1b[32mGERENCIAMENTO DE PONTO\x1b[0m\n" << endl;

    try {
        int mes, ano;

        cout << "\x1b[1mMês:\x1b[0m ";

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << "\x1b[1mAno:\x1b[0m ";

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lanca execao quando o mes informado esta fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lanca execao quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\n\x1b[0m");
        }

        limpaTela();
        this->chefe.checarPonto(mes, ano);
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }
}

void Menu::calcularSalarioFuncionarios() {
    
    cout << "\x1b[1m\x1b[32mGERENCIAMENTO DE SALÁRIO\x1b[0m\n" << endl;

    try {
        int mes, ano;

        cout << "\x1b[1mMês:\x1b[0m ";

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << "\x1b[1mAno:\x1b[0m ";

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lanca execao quando o mes informado esta fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lanca execao quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\n\x1b[0m");
        }

        limpaTela();
        this->chefe.calcularSalario(mes, ano);
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }
}

// -------------------- Metodos do funcionario

void Menu::cadastrarPonto() {

    cout << "\x1b[1m\x1b[32mCADASTRO DE PONTO\x1b[0m\n" << endl;
    
    try {
        int hora, minuto;

        cout << "\x1b[1mHora de entrada (HH MM):\x1b[0m ";

        if(!(cin >> hora >> minuto)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        Horario entrada(hora, minuto);

        cout << "\x1b[1mHora de saída (HH MM):\x1b[0m ";

        if(!(cin >> hora >> minuto)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        Horario saida(hora, minuto);

        int dia, mes, ano;

        cout << "\x1b[1mDia:\x1b[0m ";

        if(!(cin >> dia)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << "\x1b[1mMês:\x1b[0m ";

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << "\x1b[1mAno:\x1b[0m ";

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lanca execao quando o mes informado esta fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lanca execao quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\n\x1b[0m");
        }

        Data data(dia, mes, ano);
        Ponto novoPonto(data, entrada, saida);

        this->funcionario->cadastrarPonto(novoPonto);

        limpaTela();
        cout << "\n\x1b[1m\x1b[32mNovo ponto cadastrado com sucesso!\x1b[0m\n" << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }
}

void Menu::exibirSalario() {

    cout << "\x1b[1m\x1b[32mVERIFICAÇÃO DE SALÁRIO\x1b[0m\n" << endl;

    try {
        int mes, ano;

        cout << "\x1b[1mMês:\x1b[0m ";

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << "\x1b[1mAno:\x1b[0m ";

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lanca execao quando o mes informado esta fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lanca execao quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\n\x1b[0m");
        }

        limpaTela();
        this->funcionario->exibirSalario(mes, ano);
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }
}

void Menu::cadastrarVenda() {

    cout << "\x1b[1m\x1b[32mCADASTRO DE VENDA\x1b[0m\n" << endl;

    try {
        int dia, mes, ano;
        double valor;

        cout << "\x1b[1mDia:\x1b[0m ";

        if(!(cin >> dia)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << "\x1b[1mMês:\x1b[0m ";

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << "\x1b[1mAno:\x1b[0m ";

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lanca execao quando o mes informado esta fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lanca execao quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\n\x1b[0m");
        }

        Data data(dia, mes, ano);

        cout << "\x1b[1mValor:\x1b[0m ";

        if(!(cin >> valor)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        Vendedor *vendedor = static_cast<Vendedor*>(this->funcionario);
        vendedor->cadastrarVenda(Venda(valor, data));

        limpaTela();
        cout << "\n\x1b[1m\x1b[32mNova venda cadastrada com sucesso!\x1b[0m\n" << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << "\n\x1b[1m\x1b[31mErro: \x1b[0m" << e.what() << endl;
    }
}

void Menu::listarVenda() {
    this->funcionario->listarVendas();
}

// Limpa a tela no terminal
void Menu::limpaTela() {
    // CSI[2J limpa a tela, CSI[H move o cursor de volta pro topo na esquerda
    cout << "\x1B[2J\x1B[H";
}