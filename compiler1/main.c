#include "compiler.h"
#include "helpers/vector.h"
#include <stdio.h>

extern void print_ast(struct node* node, int indent);
extern struct compile_process* last_process;  // <- Aqui acessamos o processo global

int main() {
    printf("Compiladores – TURMA A/B – GRUPO X\n\n");

    int res = compile_file("test.c", NULL, 0);
    if (res == COMPILER_FAILED_WITH_ERRORS) {
        printf("Erro de compilação!\n");
        return 1;
    }

    printf("Todos os arquivos foram compilados com sucesso!\n\n");

    if (!last_process) {
    printf("Erro: last_process está nulo!\n");
    return 1;
}

    if (!last_process->node_tree_vec || vector_count(last_process->node_tree_vec) == 0) {
        printf("Erro: AST não foi construída corretamente.\n");
        return 1;
    }

    struct node* root = *(struct node**) vector_at(last_process->node_tree_vec, 0);
    print_ast(root, 0);


    return 0;
}
