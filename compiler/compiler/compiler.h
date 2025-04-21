#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

/* BEGIN - LAB 2 ---------------------------------*/

struct pos {
    int line;
    int col;
    const char* filename;
};

#define TOKEN_TYPE_PREPROCESSOR 10

#define NUMERIC_CASE \
    case '0':   \
    case '1':   \
    case '2':   \
    case '3':   \
    case '4':   \
    case '5':   \
    case '6':   \
    case '7':   \
    case '8':   \
    case '9'

enum {
    LEXICAL_ANALYSIS_ALL_OK,
    LEXICAL_ANALYSIS_IMPUT_ERROR
};

enum {
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
};

struct token { 
    int type;
    int flags;

    struct pos pos;

    union {
        char cval;
        const char *sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };

    bool whitespace;
    const char* between_brackets;
};

struct lex_process;

typedef char (*LEX_PROCESS_NEXT_CHAR)(struct lex_process* process);            
typedef char (*LEX_PROCESS_PEEK_CHAR)(struct lex_process* process);            
typedef void (*LEX_PROCESS_PUSH_CHAR)(struct lex_process* process, char c);
typedef char (*LEX_PROCESS_PEEK_AHEAD)(struct lex_process* process, int offset);

struct lex_process_functions {
    LEX_PROCESS_NEXT_CHAR next_char;
    LEX_PROCESS_PEEK_CHAR peek_char;
    LEX_PROCESS_PUSH_CHAR push_char;
    LEX_PROCESS_PEEK_AHEAD peek_ahead;
};

struct lex_process {
    struct pos pos;
    struct vector* token_vec;
    struct compile_process* compiler;
    
    int current_expression_count;

    struct buffer* parentheses_buffer;
    struct lex_process_functions* function;

    void* private;
    const char* input;
    int input_size;
};

// cprocess.c
char compile_process_next_char(struct lex_process* lex_process);
char compile_process_peek_char(struct lex_process* lex_process);
void compile_process_push_char(struct lex_process* lex_process, char c);

// lex_process.c
struct lex_process* lex_process_create(struct compile_process* compiler, struct lex_process_functions* functions, void *private);
void lex_process_free(struct lex_process* process);
void* lex_process_private(struct lex_process* process);
struct vector* lex_process_tokens(struct lex_process* process);

// lexer.c
int lex(struct lex_process* process);

// compiler.c
void compiler_error(struct compile_process* compiler, const char* msg, ...);
void compiler_warning(struct compile_process* compiler, const char* msg, ...);

/* END - LAB 2 ---------------------------------*/

enum {
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FAILED_WITH_ERRORS
};

struct compile_process {
    int flags;

    struct pos pos;

    struct compile_process_input_file {
        FILE* fp;
        const char* abs_path;
    } cfile;

    struct vector* token_vec;       // LAB3: Vetor de tokens da análise léxica
    struct vector* node_vec;        // LAB3: Vetor de nodes da análise sintática
    struct vector* node_tree_vec;   // LAB3: Raiz da árvore de análise

    FILE* ofile;
};

// LAB3: Tipos de nós da árvore sintática
enum {
    NODE_TYPE_EXPRESSION,
    NODE_TYPE_EXPRESSION_PARENTHESES,
    NODE_TYPE_NUMBER,
    NODE_TYPE_IDENTIFIER,
    NODE_TYPE_STRING,
    NODE_TYPE_VARIABLE,
    NODE_TYPE_VARIABLE_LIST,
    NODE_TYPE_FUNCTION,
    NODE_TYPE_BODY,
    NODE_TYPE_STATEMENT_RETURN,
    NODE_TYPE_STATEMENT_IF,
    NODE_TYPE_STATEMENT_ELSE,
    NODE_TYPE_STATEMENT_WHILE,
    NODE_TYPE_STATEMENT_DO_WHILE,
    NODE_TYPE_STATEMENT_FOR,
    NODE_TYPE_STATEMENT_BREAK,
    NODE_TYPE_STATEMENT_CONTINUE,
    NODE_TYPE_STATEMENT_SWITCH,
    NODE_TYPE_STATEMENT_CASE,
    NODE_TYPE_STATEMENT_DEFAULT,
    NODE_TYPE_STATEMENT_GOTO,
    NODE_TYPE_UNARY,
    NODE_TYPE_TENARY,
    NODE_TYPE_LABEL,
    NODE_TYPE_STRUCT,
    NODE_TYPE_UNION,
    NODE_TYPE_BRACKET,
    NODE_TYPE_CAST,
    NODE_TYPE_BLANK,
};

// LAB3: Erros de parsing
enum {
    PARSE_ALL_OK,
    PARSE_GENERAL_ERROR
};

// LAB3: Estrutura de um nó sintático
struct node {
    int type;
    int flags;
    struct pos pos;

    struct node_binded {
        struct node* owner;   // Ponteiro para o body node
        struct node* funtion; // Ponteiro para a função que o nó está
    } binded;

    union {
        char cval;
        const char* sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };
};

#endif // COMPILER_H