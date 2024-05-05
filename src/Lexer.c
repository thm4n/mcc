#include "Lexer.h"

int lexer(char* inputFilePath, vector* tokens) {
	FILE* inFile = NULL;
	char token[32] = {0};
	char ch = 0;

	inFile = fopen(inputFilePath, "r");
	if(!inFile) {
		errlog(ERRCODE_IO_MSG);
		return _errcode_IO;
	}

	while(fread(&ch, 1, 1, inFile) == 1) {
		
	}

	return _errcode_clean;
}
