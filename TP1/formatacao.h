#ifndef FORMATACAO_H
#define FORMATACAO_H

// Cores e formatos de texto
#define RESETA           "\x1b[0m"  // desativa os efeitos anteriores
#define NEGRITO          "\x1b[1m"  // coloca o texto em negrito
#define VERMELHO         "\x1b[31m" // vermelho
#define VERDE            "\x1b[32m" // verde
#define AMARELO          "\x1b[33m" // amarelo
#define AZUL             "\x1b[34m" // azul
#define CIANO            "\x1b[36m" // ciano
#define VERMELHO_NEGRITO "\x1b[1m\x1b[31m" // vermelho + negrito
#define VERDE_NEGRITO    "\x1b[1m\x1b[32m" // verde + negrito
#define AMARELO_NEGRITO  "\x1b[1m\x1b[33m" // amarelo + negrito
#define AZUL_NEGRITO     "\x1b[1m\x1b[34m" // azul + negrito
#define CIANO_NEGRITO    "\x1b[1m\x1b[36m" // ciano + negrito

// Quantidade padrão de horas diárias trabalhadas
#define HORAS_DIARIAS 8
// Quantidade máxima de horas permitidas em um dia com hora extra
#define MAXIMO_HORAS_DIARIAS 10

// Quantidade padrão de horas semanais trabalhadas
#define HORAS_SEMANAIS 40
// Quantidade máxima de horas permitidas em uma semana com hora extra
#define MAXIMO_HORAS_SEMANAIS 50

// Quantidade padrão de horas mensais trabalhadas
#define HORAS_MENSAIS 160
// Quantidade máxima de horas permitidas em um mês com hora extra
#define MAXIMO_HORAS_MENSAIS 200

#endif