#include "Header.h"

int main(int argc, char** argv) {
	initLogger(argc, argv);

	if(argc != 2) {
		errlog(ERRCODE_USAGE_MSG);
		return _errcode_usage;
	}

	vector* tokens = vector_ctor();

	lexer(argv[1], tokens);

	for(int i = 0; i < tokens->_length; i++) {
		dbglog("tok[%d]: '%s'", i + 1, tokens->_array[i]);
		if(tokens->_array[i])
			free(tokens->_array[i]);
	}
	vector_dtor(tokens);

	return 0;
}
