#ifndef _LEXER_H_
#define _LEXER_H_

#include "Header.h"
#include "Token.h"

typedef struct Lexer {
    char _filePath[FILENAME_MAX_LENGTH];
    FILE* _fd;
    
    int _offset;
    int _line;
    int _col;

    Token* _tokens[TOKEN_CACHE_SIZE];
    int _tokensIndex;
    
    Token** _tokensArray;
    int _tokensArrayLength;
} Lexer;


int getNextToken(Lexer* lexedFile);

int lexer(Lexer** lexedFile, const char* filePath);

#endif
