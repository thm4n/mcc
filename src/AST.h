#ifndef _AST_H_
#define _AST_H_

#include "Header.h"

enum astNode_t {
    astNode_dec,
    astNode_assign,
    astNode_expression,
};

enum astSym_t {
    astSym_void,
    astSym_int,
    astSym_char,
};

typedef struct ASTNode {
    int _nodeType;
    char _name[IDENTIFIER_MAX_LENGTH]; // ignorable
    int _symtype;
    struct ASTNode** _statements;
    int _statementsArraySize;
} ASTNode;

typedef struct AST {
    char _file[FILENAME_MAX_LENGTH];
    ASTNode** _statements;
    int _statementsArraySize;

    Token** _tokens;
    int _currToken;
    int _tokensArraySize;
} AST;

#endif