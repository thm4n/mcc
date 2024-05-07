#include "Header.h"

int handleFile(char* filePath);

int main(int argc, char** argv) {
	int res = 0;

	initLogger(argc, argv);

	if(argc <=  1) {
		errlog(ERRCODE_USAGE_MSG);
		return _errcode_usage;
	}

	for(int i = 1; i < argc; i++) {
		if((res = handleFile(argv[i]))) {
			dbglog("handleFile failed with errno: %d", res);
			return res;
		}
	}

	return 0;
}

int handleFile(char* filePath) {
	vector* tokens = vector_ctor();

	int res = lexer(filePath, tokens);

	if(res != EXIT_SUCCESS) {
		dbglog("lexer failed with errno: %d", res);
		return res;
	}

	printf("------- %s -------\n", filePath);
	for(int i = 0; i < tokens->_length; i++) {
		printf("tok[%d]: '%s'\n", i + 1, (char*)tokens->_array[i]);
		if(tokens->_array[i])
			free(tokens->_array[i]);
	}
	vector_dtor(tokens);

	return 0;
}
