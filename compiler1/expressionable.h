#ifndef EXPRESSIONABLE_H
#define EXPRESSIONABLE_H

// Total de grupos de precedência definidos no expressionable.c
#define TOTAL_OPERADOR_GROUPS 14

// Número máximo de operadores por grupo (ajustado para comportar até 14, incluindo o NULL)
#define MAX_OPERATORS_IN_GROUP 14

// Associação dos operadores
#define ASSOCIATIVITY_LEFT_TO_RIGHT 0
#define ASSOCIATIVITY_RIGHT_TO_LEFT 1

// Estrutura que representa um grupo de operadores com mesma precedência
struct expressionable_op_precedence_group {
    const char* operators[MAX_OPERATORS_IN_GROUP]; // Lista de operadores (terminada em NULL)
    int associativity;                             // Associação: esquerda → direita ou direita → esquerda
};

// Tabela global de precedência de operadores
extern struct expressionable_op_precedence_group op_precedence[TOTAL_OPERADOR_GROUPS];

#endif
