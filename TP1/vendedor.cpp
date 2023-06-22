#include <iostream>
#include <iomanip>
#include <string>

#include "pessoa.h"
#include "funcionario.h"
#include "vendedor.h"
#include "venda.h"
#include "data.h"
#include "formatacao.h"

using namespace std;

// Construtor da classe Vendedor
Vendedor::Vendedor(string nome, string usuario, string senha, string tipoFuncionario,
    string funcao, double salarioPorHora) :
    Funcionario(nome, usuario, senha, tipoFuncionario, funcao, salarioPorHora) {}

// Destrutor da classe Vendedor
Vendedor::~Vendedor() {}

// Cadastra uma venda do vendedor
void Vendedor::cadastrarVenda(Venda venda) {
    this->vendas.push_back(venda);
}

// Calcula o valor das vendas do vendedor
double Vendedor::calcularVendas(int mes, int ano) {

    // Lanca execao quando o mes informado esta fora do intervalo correto
    if(mes < 1 || mes > 12) {
        throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
    }

    double valorVendas = 0.;

    for(Venda venda: this->vendas) {

        // Se o ano do ponto analisado for maior do que o ano requerido, para
        if(venda.getData().getAno() > ano)
            break;

        // Se o ano do ponto analisado for menor do que o ano requerido, continua
        else if (venda.getData().getAno() < ano)
            continue;

        // Se o ano do ponto analisado for o ano requerido, soma as horas
        else if(venda.getData().getMes() == mes && venda.getData().getAno() == ano)
            valorVendas += venda.getValor();
    }
    return valorVendas;
}

// Imprime todas as vendas do vendedor
void Vendedor::listarVendas() {
    // Variavel que armazena o dia da venda
    int diaVenda = -1;
    for(auto element: this->vendas) {
        // Se as vendas forem em dias diferentes, printa o dia das vendas e atualiza a variável
        if(!(element.getData().getDia() == diaVenda)){
            cout << "\t" "\x1b[34m" << element.getData() << "\x1b[0m" << endl;
            diaVenda = element.getData().getDia();
        }
        cout << element << endl;
    }
}

// Calcula o salario do vendedor em funcao das horas trabalhadas, horas pendentes e bonificacoes
double Vendedor::calcularSalario(int mes, int ano) {

    double vendasMensais = Vendedor::calcularVendas(mes, ano);
    double horasMensais = Vendedor::calculaHorasMensais(mes, ano);
    
    double horasExtra = horasMensais - HORAS_MENSAIS;

    // Se tiver horas extra, diminui das mensais para calcular estas normalmente,
    // ja que as horas extra tem bonificacao
    if(horasExtra > 0)
        horasMensais -= horasExtra;

    // Se as horas extra forem negativas, reseta para 0, ja que nao tem
    else
        horasExtra = 0;

    // Retorna o salario com a bonificacao de vendas (10%) e as horas extra (100%)
    return vendasMensais * .1 + horasMensais * getSalarioPorHora() +
        horasExtra * getSalarioPorHora() * 2;  
}

// Exibe o salario do supervisor e a data referente a ele
void Vendedor::exibirSalario(int mes, int ano) {
    // Aqui usamos setw para padronizar a impressao como MM/AAAA
    // e setfill para preencher com 0 pela esquerda
    cout << "\x1b[1m\x1b[34m" << Vendedor::getNome() << ":" << "\x1b[0m" << endl
        << "\t" << "Salário de \x1b[1m" << setw(2) << setfill('0') << mes << "/" << ano << "\x1b[0m: "
        << "R$ " << calcularSalario(mes, ano);
}

// Sobrecarga do cout para imprimir nome e usuario do vendedor
ostream &operator <<(ostream &out, const Vendedor &objeto) {
    out << "\x1b[1m\x1b[34m" << objeto.getNome() << "\x1b[0m" << endl
        << "\t" << "\x1b[1mUsuário:\x1b[0m " << objeto.getUsuario() << endl
        << "\t" << "\x1b[1mTipo de funcionário:\x1b[0m " << objeto.getTipoFuncionario() << endl
        << "\t" << "\x1b[1mFunção:\x1b[0m " << objeto.getFuncao();
    return out;
}