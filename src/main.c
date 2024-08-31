#include "Header.h"

#include "Lexer.h"

int main(int argc, char** argv) {
	// currently in main: will be transfered:
	if(argc == 1) {
		errlog("cant compile nothing - dumbass");
		return 1;
	}
	if(argc > 2) {
		errlog("i dont support more than one soruce file..");
		return 1;
	}

	dbglog("currently only checking lexer");
	Lexer* lexedFile = NULL;
	lexer(lexedFile, argv[1]);
	dbglog("lexer returned with lexed file");

	printf("lexedFile->_filePath: %s", lexedFile->_filePath);
	printf("lexedFile->_tokensLength: %s", lexedFile->_filePath);
	Token* tok = NULL;
	for(int i = 0; i < lexedFile->_tokensLength; i++) {
		tok = &(lexedFile->_tokens[i]);
		printf("Token:\n >> file: %s\n >> line, col, offset: (%d, %d) - %d\n >> length: %d\n >> value: %s",
				tok->_filePath, tok->_line, tok->_col, tok->_offset, tok->_len, tok->_value);
	}
	return 0;
}
