#include <stdio.h>
#include "helpers/vector.h"

int main() {
    printf("Compiladores - TURMA asd\n");

    // Criando um vetor para armazenar inteiros
    struct vector* vec = vector_create(sizeof(int));

    if (!vec) {
        printf("Erro ao criar o vetor.\n");
        return 1;
    }

    // Adicionando elementos ao vetor
    int a = 10, b = 20, c = 30;
    vector_push(vec, &a);
    vector_push(vec, &b);
    vector_push(vec, &c);

    printf("Elementos inseridos: %d, %d, %d\n", a, b, c);

    // Acessando os elementos
    printf("Elemento no índice 0: %d\n", *(int*)vector_at(vec, 0));
    printf("Elemento no índice 1: %d\n", *(int*)vector_at(vec, 1));
    printf("Elemento no índice 2: %d\n", *(int*)vector_at(vec, 2));

    // Removendo um elemento
    vector_pop(vec);
    printf("Último elemento removido.\n");

    // Verificando o novo último elemento
    printf("Novo último elemento: %d\n", *(int*)vector_back(vec));

    // Liberando a memória alocada
    vector_free(vec);

    return 0;
}
