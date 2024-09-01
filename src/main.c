#include "Header.h"

#include "Lexer.h"

int main(int argc, char** argv) {
	int ret = SUCCESS;
	Lexer* lexedFile = NULL;
	Token* tok = NULL;

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
	ret = lexer(&lexedFile, argv[1]);
	if(ret != SUCCESS) {
		errlog("lexer failed with error %d", ret);
		goto __main_end;
	}
	dbglog("lexer returned with lexed file");

	printf("lexedFile->_filePath: %s", lexedFile->_filePath);
	printf("lexedFile->_tokensArrayLength: %d", lexedFile->_tokensArrayLength);
	for(int i = 0; i < lexedFile->_tokensArrayLength; i++) {
		tok = lexedFile->_tokensArray[i];
		printf("Token:\n >> file: %s\n >> line, col, offset: (%d, %d) - %d\n >> length: %d\n >> value: '%s'",
				tok->_filePath, tok->_line, tok->_col, tok->_offset, tok->_len, tok->_value);
	}

__main_end:
	if(lexedFile) {
		dbglog("Deallocating 'lexedFile'");
		free(lexedFile);
	}
	return 0;
}
