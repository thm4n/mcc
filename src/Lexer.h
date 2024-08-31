#ifndef _LEXER_H_
#define _LEXER_H_

#include "Header.h"
#include "Token.h"

typedef struct Lexer {
    char* _filePath;
    FILE* _fd;
    
    int _offset;
    int _line;
    int _col;

    Token* _tokens;
    int _tokensLength;
} Lexer;

int lexer(Lexer* lexedFile, const char* filePath);

#endif
