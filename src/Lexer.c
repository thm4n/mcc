#include "Lexer.h"

#define TOK_SIZE 32

int lexer(char* inputFilePath, vector* tokens) {
	FILE* inFile = NULL;
	char token[TOK_SIZE] = {0};
	char* str = NULL;
	int index = 0;
	char ch = 0;

	inFile = fopen(inputFilePath, "r");
	if(!inFile) {
		errlog(ERRCODE_IO_MSG);
		return _errcode_IO;
	}

	while(!feof(inFile) && index < TOK_SIZE) {
		if(fread(&ch, 1, 1, inFile) != 1) {
			dbglog("fread returned != 1: ch holds value %d", (int)ch);
		}

		if(isWS(ch)) {
			if(index) {
				str = allocateStr(token, 0);
				vector_append(tokens, str);
				memset(token, 0, TOK_SIZE);
				index = 0;
			}
			else {
				dbglog("tried to append to tokens vector empty token");
			}
		}
		else if(isChar(ch) || isDigit(ch)) {
			token[index++] = ch;
		}
		else if(isSpec(ch)) {
			if(index) {
				str = allocateStr(token, 0);
				vector_append(tokens, str);
				memset(token, 0, TOK_SIZE);
				index = 0;
			}
			str = allocateStr(&ch, 1);
			vector_append(tokens, str);
		}
	}

	if(index) {
		str = allocateStr(token, 0);
		vector_append(tokens, str);
		memset(token, 0, TOK_SIZE);
		index = 0;
	}

	fclose(inFile);

	return _errcode_clean;
}
