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
    this->chefe = Chefe("Fulano", "admin", "admin", 100000);
    this->funcionario = NULL;
    this->tipoFuncionario = static_cast<tipoMenu>(tipoFuncionario);
    
    Funcionario *A = new Supervisor("Ciclano", "ciclano", "ciclano", "Supervisor", "Supervisiona os vendedores", 1000.);
    Funcionario *B = new Vendedor("Beltrano", "beltrano", "beltrano", "Vendedor", "Vendedor de sonhos", 300.);

    this->chefe.cadastrarFuncionario(A);
    this->chefe.cadastrarFuncionario(B);

    Supervisor *C = static_cast<Supervisor*>(A);
    Vendedor *D = static_cast<Vendedor*>(B);

    C->adicionarSupervisionado(D);
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

// Checa se as informações de login batem com algum usuário existente
bool Menu::checaLogin(string usuario, string senha) {
    
    // Se as informações de login forem iguais às do chefe, seta o menu do chefe
    if(this->chefe.getUsuario() == usuario && this->chefe.getSenha() == senha) {
        this->setMenu(1);
        return true;
    }

    // Senão, checa se as informações de login equivalem às de algum funcionário
    else {
        for(Funcionario* pFuncionario: this->chefe.getFuncionarios()) {
            if(pFuncionario->getUsuario() == usuario && pFuncionario->getSenha() == senha) {
                // Se bater com as informações de login de um supervisor, seta o menu do supervisor
                if(pFuncionario->getTipoFuncionario() == "Supervisor")
                    this->setMenu(2);
                // Se bater com as informações de login de um vendedor, seta o menu do vendedor
                else if(pFuncionario->getTipoFuncionario() == "Vendedor")
                    this->setMenu(3);
                
                this->funcionario = pFuncionario;
                return true;
            }
        }
    }
    
    return false;
}

// Loop para o login e logout
void Menu::login() {

    string usuario, senha;
    
    // Loop que pede o login enquanto um login inválido é informado
    while(true) {
        try {
            cout << VERDE_NEGRITO << "Faça o login ou digite -1 para sair." << RESETA << "\n" << endl;
            
            // Recebe o usuário
            cout << AZUL_NEGRITO << "Usuário: " << RESETA;
            cin >> usuario;

            // Se receber um -1, o programa encerra
            if(usuario == "-1") {
                limpaTela();
                cout << VERDE_NEGRITO << "\n" << "Logout efetuado com sucesso! Até a próxima :(" << RESETA << endl;
                
                break;
            }
            
            // Recebe a senha
            cout << AZUL_NEGRITO << "Senha: " << RESETA;
            cin >> senha;
            cout << endl;
            
            // Confere se as informações de login estão corretas
            // Se sim, realiza o login
            if(checaLogin(usuario, senha)) {
                limpaTela();
                cout << VERDE_NEGRITO << "Login efetuado com sucesso!" << RESETA << "\n" << endl;
                cout << AZUL_NEGRITO << "Bem Vindo(a) ";

                // if(this->tipoFuncionario == 1)? this->chefe.getNome() : this->funcionario->getNome() << " - ";

                if(this->tipoFuncionario == 1)
                    cout << this->chefe.getNome() << endl;
                    
                else {
                    cout << this->funcionario->getNome() << " - ";

                    if(this->tipoFuncionario == 2)
                        cout << "Supervisor" << endl;
                        
                    else if(this->tipoFuncionario == 3)
                        cout << "Vendedor" << endl;
                }

                cout << RESETA;

                this->opcoes();
            }
            
            // Senão, informa que o usuário ou a senha estão inválidos
            // e o loop volta no início
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
            cout << VERMELHO_NEGRITO << "Erro: Digite um valor válido." << RESETA << endl;
        }
        
        // Pega a exceção UsuarioSenhaInvalida, que foi criada por nós, caso não seja encontrado nenhum usuário cadastrado com os valores informados
        catch(UsuarioSenhaInvalido& e) {
            limpaTela();
            cout << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
        }
    }
}

// Lista as opções
void Menu::mostrarOpcoes() {
    
    // Mostra as opções do menu do chefe
    if(this->getMenu() == 1) {
        cout << "1 - Cadastrar funcionário." << endl;
        cout << "2 - Listar funcionários." << endl;
        cout << "3 - Mostrar ponto dos funcionários." << endl;
        cout << "4 - Exbir salário dos funcionários." << endl;
        cout << "0 - Voltar.\n" << endl;
    }
    
    // Mostra as opções do menu do funcionário
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

// Loop para selecionar as opções e voltar para o menu
void Menu::opcoes() {

    int opcao;

    while(true) {
        
        cout << endl;
        this->mostrarOpcoes();

        try {
            // Valida o valor, retornando erro se não for um inteiro
            if(!(cin >> opcao)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
                limpaTela();
                throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
            }
            
            // Valida a opção, retornando erro se for inválida
            if(opcao < 0 || ( (this->getMenu() == 2) && (opcao > 3)) || ((this->getMenu() == 3) && (opcao > 5)) || ((this->getMenu() == 1) && (opcao > 5))) {
                limpaTela();
                throw invalid_argument("\x1b[1m\x1b[31mInsira somente a opção desejada.\n\x1b[0m");
            }

            cout << endl;
            limpaTela();
            
            // Opções para o chefe
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

            // Opções para o funcionário
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

            cout << AMARELO_NEGRITO << "----------------------------------------" << RESETA << endl;
        }
        
        // Retorna o erro que ocorreu no try
        catch(invalid_argument &e) {
            cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
        }
    }
}

// -------------------- Métodos do chefe

void Menu::cadastrarFuncionario() {
    
    string nome, usuario, senha, tipoFuncionario, funcao;
    double salarioPorHora;

    cout << VERDE_NEGRITO << "CADASTRO DE FUNCIONÁRIO" << RESETA << "\n" << endl;

    // Pega as informações do novo funcionário
    try {
        cout << NEGRITO << "Nome: " << RESETA;
        cin >> nome;

        cout << NEGRITO << "Usuário: " << RESETA;
        cin >> usuario;

        cout << NEGRITO << "Senha: " << RESETA;
        cin >> senha;

        cout << NEGRITO << "Tipo de funcionário: " << RESETA;
        cin >> tipoFuncionario;

        if(!(tipoFuncionario == "Supervisor" || tipoFuncionario == "Vendedor")) {
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mErro: Tipo de funcionário deve ser \"Supervisor\" ou \"Vendedor\".\n\x1b[0m");
        }
        
        cin.ignore(1000, '\n');
        cout << NEGRITO << "Função: " << RESETA;
        // cin >> funcao;
        getline(cin, funcao);


        cout << NEGRITO << "Salário por hora: " << RESETA;

        if(!(cin >> salarioPorHora)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Cadastra o funcionário com a classe correspondente
        
        if(tipoFuncionario == "Supervisor") {
            Funcionario *novoFuncionario = new Supervisor(nome, usuario, senha, tipoFuncionario, funcao, salarioPorHora);
            this->chefe.cadastrarFuncionario(novoFuncionario);
        }

        else {
            Funcionario *novoFuncionario = new Vendedor(nome, usuario, senha, tipoFuncionario, funcao, salarioPorHora);
            this->chefe.cadastrarFuncionario(novoFuncionario);
            
            for(Funcionario *pFuncionario: this->chefe.getFuncionarios()) {
                if (pFuncionario->getTipoFuncionario() == "Supervisor") {
                    Supervisor *pSupervisor = static_cast<Supervisor*>(pFuncionario);

                    Vendedor *pVendedor = static_cast<Vendedor*>(novoFuncionario);

                    pSupervisor->adicionarSupervisionado(pVendedor);
                }
            }
        }

        limpaTela();
        cout << VERDE_NEGRITO << "Novo funcionário cadastrado com sucesso!" << RESETA << "\n" << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna erro quando o usuário já existe
    catch(UsuarioJaExistente &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }
}

void Menu::listarFuncionarios() {
    cout << VERDE_NEGRITO << "FUNCIONÁRIOS CADASTRADOS" << RESETA << "\n" << endl;
    this->chefe.listarFuncionarios();
}

void Menu::mostrarPontoFuncionarios() {

    cout << VERDE_NEGRITO << "GERENCIAMENTO DE PONTO" << RESETA << "\n" << endl;

    try {
        int mes, ano;

        cout << NEGRITO << "Mês: " << RESETA;

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << NEGRITO << "Ano: " << RESETA;

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lança exceção quando o mês informado está fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lança exceção quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\n\x1b[0m");
        }

        limpaTela();
        this->chefe.checarPonto(mes, ano);
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }
}

void Menu::calcularSalarioFuncionarios() {
    
    cout << VERDE_NEGRITO << "GERENCIAMENTO DE SALÁRIO" << RESETA << "\n" << endl;

    try {
        int mes, ano;

        cout << NEGRITO << "Mês: " << RESETA;

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << NEGRITO << "Ano: " << RESETA;

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lança exceção quando o mês informado está fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lança exceção quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\n\x1b[0m");
        }

        limpaTela();
        this->chefe.calcularSalario(mes, ano);
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }
}

// -------------------- Métodos do funcionário

void Menu::cadastrarPonto() {

    cout << VERDE_NEGRITO << "CADASTRO DE PONTO" << RESETA << "\n" << endl;
    
    try {
        int hora, minuto;

        cout << NEGRITO << "Hora de entrada (HH MM): " << RESETA;

        if(!(cin >> hora >> minuto)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        Horario entrada(hora, minuto);

        cout << NEGRITO << "Hora de saída (HH MM): " << RESETA;

        if(!(cin >> hora >> minuto)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        Horario saida(hora, minuto);

        int dia, mes, ano;

        cout << NEGRITO << "Dia: " << RESETA;

        if(!(cin >> dia)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << NEGRITO << "Mês: " << RESETA;

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << NEGRITO << "Ano: " << RESETA;

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lança exceção quando o mês informado está fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lança exceção quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\x1b[0m");
        }

        Data data(dia, mes, ano);
        Ponto *novoPonto = new Ponto(data, entrada, saida);

        this->funcionario->cadastrarPonto(novoPonto);

        limpaTela();
        cout << VERDE_NEGRITO << "Novo ponto cadastrado com sucesso!\n" << RESETA << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }
}

void Menu::exibirSalario() {

    cout << VERDE_NEGRITO << "VERIFICAÇÃO DE SALÁRIO" << RESETA << "\n" << endl;

    try {
        int mes, ano;

        cout << NEGRITO << "Mês: " << RESETA;

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << NEGRITO << "Ano: " << RESETA;

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lança exceção quando o mês informado está fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lança exceção quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\n\x1b[0m");
        }

        limpaTela();
        this->funcionario->exibirSalario(mes, ano);
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }
}

void Menu::cadastrarVenda() {

    cout << VERDE_NEGRITO << "CADASTRO DE VENDA" << RESETA "\n" << endl;

    try {
        int dia, mes, ano;
        double valor;

        cout << NEGRITO << "Dia: " << RESETA;

        if(!(cin >> dia)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << NEGRITO << "Mês: " << RESETA;

        if(!(cin >> mes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        cout << NEGRITO << "Ano: " << RESETA;

        if(!(cin >> ano)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        // Lança exceção quando o mês informado está fora do intervalo correto
        if(mes < 1 || mes > 12) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
        }

        // Lança exceção quando o ano informado for negativo
        else if(ano < 0) {
            limpaTela();
            throw out_of_range("\x1b[1m\x1b[31mAnos devem ser positivos.\n\x1b[0m");
        }

        Data data(dia, mes, ano);

        cout << NEGRITO << "Valor: " << RESETA;

        if(!(cin >> valor)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignora \n no buffer
            limpaTela();
            throw invalid_argument("\x1b[1m\x1b[31mInsira um valor válido.\n\x1b[0m");
        }

        Vendedor *vendedor = static_cast<Vendedor*>(this->funcionario);
        vendedor->cadastrarVenda(new Venda(valor, data));

        limpaTela();
        cout << VERDE_NEGRITO << "Nova venda cadastrada com sucesso!\n" << RESETA << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(invalid_argument &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna erro quando algum argumento é inválido
    catch(out_of_range &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }

    // Retorna o erro que ocorreu no try
    catch(exception &e) {
        cerr << VERMELHO_NEGRITO << "Erro: " << RESETA << e.what() << endl;
    }
}

void Menu::listarVenda() {
    this->funcionario->listarVendas();
}

// Limpa a tela do terminal
void Menu::limpaTela() {
    // CSI[2J limpa a tela, CSI[H move o cursor de volta pro topo na esquerda
    cout << "\x1B[2J\x1B[H";
}