#include "compiler.h"
#include "expressionable.h"

// Formato: {operator1, operator2, ..., NULL}
struct expressionable_op_precedence_group op_precedence[TOTAL_OPERADOR_GROUPS] = {
    { .operators = {"++", "--", "()", "[]", "(", "[", ".", "->", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"*", "/", "%", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"+", "-", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"<<", ">>", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"<", "<=", ">", ">=", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"==", "!=", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"&", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"^", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"|", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"&&", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"||", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT },
    { .operators = {"?", ":", NULL}, .associativity = ASSOCIATIVITY_RIGHT_TO_LEFT },
    { .operators = {"=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=", NULL}, .associativity = ASSOCIATIVITY_RIGHT_TO_LEFT },
    { .operators = {",", NULL}, .associativity = ASSOCIATIVITY_LEFT_TO_RIGHT }
};
