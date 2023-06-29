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
Vendedor::~Vendedor() {
    this->liberaVendas();
}

// Cadastra uma venda do vendedor
void Vendedor::cadastrarVenda(Venda *venda) {
    this->vendas.push_back(venda);
}

void Vendedor::liberaVendas(){

    for(Venda* venda : this->vendas)
        delete venda;

}

// Calcula o valor das vendas do vendedor
double Vendedor::calcularVendas(int mes, int ano) {

    // Lança exceção quando o mês informado está fora do intervalo correto
    if(mes < 1 || mes > 12) {
        throw out_of_range("\x1b[1m\x1b[31mMeses devem estar entre 1 e 12.\n\x1b[0m");
    }

    double valorVendas = 0.;

    for(Venda *pVenda: this->vendas) {

        // Se o ano do ponto analisado for maior do que o ano requerido, para
        if(pVenda->getData().getAno() > ano)
            break;

        // Se o ano do ponto analisado for menor do que o ano requerido, continua
        else if (pVenda->getData().getAno() < ano)
            continue;

        // Se o ano do ponto analisado for o ano requerido, soma as horas
        else if(pVenda->getData().getMes() == mes && pVenda->getData().getAno() == ano)
            valorVendas += pVenda->getValor();
    }

    return valorVendas;
}

// Imprime todas as vendas do vendedor
void Vendedor::listarVendas() {

    // Variável que armazena o dia da venda
    int diaVenda = -1;

    if(this->vendas.size() == 0){
        cout << VERMELHO_NEGRITO << "Nenhuma venda cadastrada." << RESETA << "\n" << endl;
        return;
    }
    
    for(Venda *pVenda: this->vendas) {
        // Se as vendas forem em dias diferentes, printa os dia das vendas e atualiza a variável
        if(!(pVenda->getData().getDia() == diaVenda)) {
            cout << "\t" << AZUL << pVenda->getData() << RESETA << endl;
            diaVenda = pVenda->getData().getDia();
        }

        cout << *pVenda << endl;
    }
}

// Calcula o salário do vendedor em função das horas trabalhadas, horas pendentes e bonificações
double Vendedor::calcularSalario(int mes, int ano) {

    double vendasMensais = Vendedor::calcularVendas(mes, ano);
    double horasMensais = Vendedor::calculaHorasMensais(mes, ano);
    
    double horasExtra = horasMensais - HORAS_MENSAIS;

    // Se tiver horas extras, diminui das mensais para calcular estas normalmente,
    // já que as horas extras têm bonificação
    if(horasExtra > 0)
        horasMensais -= horasExtra;

    // Se as horas extras forem negativas, reseta para 0, já que não tem
    else
        horasExtra = 0;

    // Retorna o salário com a bonificação de vendas (10%) e as horas extras (100%)
    return vendasMensais * .1 + horasMensais * getSalarioPorHora() +
        horasExtra * getSalarioPorHora() * 2;  
}

// Exibe o salário do supervisor e a data referente a ele
void Vendedor::exibirSalario(int mes, int ano) {
    // Aqui usamos setw para padronizar a impressão como MM/AAAA
    // e setfill para preencher com 0 pela esquerda
    cout << CIANO_NEGRITO << Vendedor::getNome() << ":" << RESETA << endl
        << "\t" << "Salário de " << NEGRITO << setw(2) << setfill('0') << mes << "/" << ano << RESETA << ": "
        << "R$ " << calcularSalario(mes, ano) << "\n" << endl;
}

// Sobrecarga do cout para imprimir nome e usuário do vendedor
ostream &operator <<(ostream &out, const Vendedor &objeto) {
    out << CIANO_NEGRITO << objeto.getNome() << RESETA << endl
        << "\t" << NEGRITO << "Usuário: " << RESETA << objeto.getUsuario() << endl
        << "\t" << NEGRITO << "Tipo de funcionário: " << RESETA << objeto.getTipoFuncionario() << endl
        << "\t" << NEGRITO << "Função: " << RESETA << objeto.getFuncao() << endl;
    return out;
}