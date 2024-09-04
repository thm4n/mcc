#ifndef _LEXER_H_
#define _LEXER_H_

#include "Header.h"
#include "Token.h"

typedef struct Lexer {
    char _filePath[FILENAME_MAX_LENGTH];
    FILE* _fd;
    
    int _file_length;
    int _offset;
    int _line;
    int _col;

    Token* _tokens[TOKEN_CACHE_SIZE];
    int _tokensIndex;
    
    Token** _tokensArray;
    int _tokensArrayLength;
} Lexer;

Token* createToken(Lexer* lexedFile);
void freeToken(Token* token);

int replaceTokensArrayCache(Lexer* lexedFile);
int addToken(Lexer* lexedFile, Token* token);

void skipWhitespace(Lexer* lexedFile);
char getNextChar(Lexer* lexedFile);
void readUntil(Lexer* lexedFile, Token* token, int (*cb)(char));
char peekNextChar(Lexer* lexedFile);
int isEndOfFile(Lexer* lexedFile);
int getNextToken(Lexer* lexedFile);

int lexer(Lexer** pLexedFile, const char* filePath);
void freeLexer(Lexer* lexedFile);

#endif
