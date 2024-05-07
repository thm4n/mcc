#include "Lexer.h"

#define MAX_TOK_SIZE 32

int lexer(char* inputFilePath, vector* tokens) {
	FILE* inFile = NULL;
	char token[MAX_TOK_SIZE] = {0};
	char* str = NULL;
	int index = 0;
	char ch = 0;

	inFile = fopen(inputFilePath, "r");
	if(!inFile) {
		errlog(ERRCODE_IO_MSG);
		return _errcode_IO;
	}

	while(!feof(inFile) && index < MAX_TOK_SIZE) {
		if(fread(&ch, 1, 1, inFile) != 1) {
			dbglog("fread returned != 1: ch holds value %d : '%c'", (int)ch, ch);
		}

		if(isWS(ch)) {
			dbglog("got ch: '%c'", ch);
			if(index) {
				dbglog("allocating str: token holds: '%s'", token);
				str = allocateStr(token, 0);
				dbglog("test for str: '%s'", str);
				vector_append(tokens, str);
				memset(token, 0, MAX_TOK_SIZE);
				index = 0;
			}
			else {
				dbglog("tried to append to tokens vector empty token");
			}
		}
		else if(isChar(ch) || isDigit(ch)) {
			dbglog("got ch: '%c'", ch);
			token[index++] = ch;
		}
		else if(isSpec(ch)) {
			dbglog("got ch: '%c'", ch);
			if(index) {
				dbglog("allocating str: token holds: '%s'", token);
				str = allocateStr(token, 0);
				vector_append(tokens, str);
				memset(token, 0, MAX_TOK_SIZE);
				index = 0;
			}
			str = allocateStr(&ch, 1);
			vector_append(tokens, str);
		}
		ch = '\0';
	}

	fclose(inFile);

	return _errcode_clean;
}
