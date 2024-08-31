#include "Lexer.h"

int lexer(Lexer* lexedFile, const char* filePath) {
	int ret = SUCCESS;

	if(lexedFile) {
		warlog("lexer recieved initialized Lexer*");
		ret = ERRCODE_USAGE;
		goto __lexer_end;
	}

	lexedFile = (Lexer*)malloc(sizeof(Lexer));
	if(!lexedFile) {
		warlog("Failed to allocate memory");
		ret = ERRCODE_ALLOC;
		goto __lexer_end;
	}
	memset(lexedFile, 0, sizeof(Lexer));

__lexer_end:
	if(ret != SUCCESS) {
		dbglog("got to __lexer_end with errcode %d", ret);
		if(lexedFile) {
			dbglog("Deallocation 'lexedFile'");
			free(lexedFile);
		}
	}

	return ret;
}
