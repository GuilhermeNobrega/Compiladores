/* BEGIN - LAB 2 ----------------------------------*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "helpers/vector.h"
#include "helpers/buffer.h"
#include "compiler.h"

#define LEX_GETC_IF(buffer, c, exp) \
    for (c = peekc(); exp; c = peekc()){ \
        buffer_write(buffer, c); \
        nextc(); \
    } \

struct token* read_next_token();
static struct lex_process* lex_process;
static struct token tmp_token;

//Nova parte
// Pegar um caracter do arquivo, sem mudar a posicao de leitura.
static char peekc() {
    return lex_process->function->peek_char(lex_process);
}

static char nextc() {
    char c = lex_process->function->next_char(lex_process);
    lex_process->pos.col += 1;
    if (c == '\n') {
        lex_process->pos.line += 1;
        lex_process->pos.col = 1;
    }
    return c;
}

// Adicionar um caracter no arquivo.
static void pushc(char c) {
    lex_process->function->push_char(lex_process, c);
}

static struct pos lex_file_position() {
    return lex_process->pos;
}

struct token* token_create(struct token* _token) {
    memcpy(&tmp_token, _token, sizeof(struct token));
    tmp_token.pos = lex_file_position();

    return &tmp_token;
}

static struct token* lexer_last_token() {
    return vector_back_or_null(lex_process->token_vec);
}

static struct token* handle_whitespace() {
    struct token* last_token = lexer_last_token();
    if (last_token) {
        last_token->whitespace = true;
    }

    nextc();
    return read_next_token();
}

const char* read_number_str() {
    const char* num = NULL;
    struct buffer* buffer = buffer_create();
    char c = peekc();
    LEX_GETC_IF(buffer, c, (c >= '0' && c <= '9'));

    // Finaliza a string.
    buffer_write(buffer, 0x00);

    printf("Token: %s\n", buffer->data);
    // Retorna o ponteiro para o buffer.
    return buffer_ptr(buffer);
}

unsigned long long read_number() {
    const char* s = read_number_str();
    return atoll(s);
}

struct token* token_make_number_for_value(unsigned long number) {
    return token_create(&(struct token){.type=TOKEN_TYPE_NUMBER, .llnum=number});
}

struct token* token_make_number() {
    return token_make_number_for_value(read_number());
}

// Funcao responsável por ler o próximo token do arquivo.
struct token* read_next_token() {
    struct token* token = NULL;
    char c = peekc();

    switch (c) {
        case EOF:
            // Fim do arquivo.
            return NULL;

        case ' ':
        case '\t':
            token = handle_whitespace();
            break;

        case '\n': // TOKEN_TYPE_NEWLINE
            nextc(); // Consumir o caractere
            token = token_create(&(struct token){.type=TOKEN_TYPE_NEWLINE});
            break;

        case ';': case '{': case '}': case '(': case ')': case ',': case '[': case ']': // TOKEN_TYPE_SYMBOL
            nextc(); // Consumir o caractere
            token = token_create(&(struct token){.type=TOKEN_TYPE_SYMBOL, .cval=c});
            printf("Token: %c\n", c);
            break;

        case '+': case '-': case '*': case '/': case '=': case '<': case '>': case '!': case '&': case '|': // TOKEN_TYPE_OPERATOR
            nextc(); // Consumir o caractere
            token = token_create(&(struct token){.type=TOKEN_TYPE_OPERATOR, .cval=c});
            printf("Token: %c\n", c);
            break;

        default:
            if (isdigit(c)) { // Se for número, processa o número
                token = token_make_number();
            } else if (isalpha(c) || c == '_') { // TOKEN_TYPE_IDENTIFIER
                struct buffer* buf = buffer_create();
                while (isalnum(peekc()) || peekc() == '_') {
                    buffer_write(buf, nextc());
                }
                buffer_write(buf, 0x00); // Finaliza a string
                token = token_create(&(struct token){.type=TOKEN_TYPE_IDENTIFIER, .sval=buffer_ptr(buf)});
                printf("Token identificador: %s\n", token->sval);
            } else {
                // Adiciona um aviso para tokens desconhecidos e continua a leitura
                printf("Caractere não reconhecido: '%c'\n", c);
                compiler_error(lex_process->compiler, "Token invalido!\n");
                nextc();
            }
            break;
    }

    return token;
}

int lex(struct lex_process* process) {
    process->current_expression_count = 0;
    process->parentheses_buffer = NULL;
    lex_process = process;
    process->pos.filename = process->compiler->cfile.abs_path;

    struct token* token = read_next_token();

    // Ler todos os tokens do arquivo de imput
    while (token) {
        vector_push(process->token_vec, token);
        token = read_next_token();
    }

    return LEXICAL_ANALYSIS_ALL_OK;
}

/* END - LAB 2 ------------------------------------*/
