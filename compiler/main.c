#include <stdio.h>
#include "helpers/vector.h"
#include "compiler.h"  // Inclui a função compile_file()
#include "teste1.h"

int main() {
    printf("Compiladores - TURMA asd\n");
    printf("Execução função multi\n");
    multi(3);
    //-----------------------------------------
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

    // Testando vector_set_peek_pointer e vector_peek
    vector_set_peek_pointer(vec, 1);
    int* peeked_value = (int*)vector_peek(vec);
    printf("Valor obtido com vector_peek(): %d\n", *peeked_value);

    // Removendo um elemento
    vector_pop(vec);
    printf("Último elemento removido.\n");

    // Verificando o novo último elemento
    printf("Novo último elemento: %d\n", *(int*)vector_back(vec));

    // Testando compile_file()
    const char* source_file = "teste.c";
    const char* output_file = "test_out";
    int compilation_result = compile_file(source_file, output_file, 0);

    if (compilation_result == COMPILER_FILE_COMPILED_OK) {
        printf("Compilação bem-sucedida: %s -> %s\n", source_file, output_file);
    } else {
        printf("Falha na compilação de %s\n", source_file);
    }

    // Liberando a memória alocada
    vector_free(vec);

    return 0;
}