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
	char* outFilePath = NULL;
	FILE* outFile = NULL;
	int res = 0;
	
	inflog("Starting 1st stage:");
	res = lexer(filePath, tokens);

	if(res != EXIT_SUCCESS) {
		inflog("1st stage failed with errno: %d", res);
		return res;
	}
	
	inflog("Finished 1st stage successfully");

	outFilePath = addFileExt(filePath, ".tok");
	inflog("Output of 1st stage stored in %s", outFilePath);
	outFile = fopen(outFilePath, "w+");
	if(!outFile) {
		exitWithError(_errcode_IO, ERRCODE_IO_MSG);
	}

	for(int i = 0; i < tokens->_length; i++) {
		fprintf(outFile, "%s\n", tokens->_array[i]);
	}

	fclose(outFile);

	// inflog("Starting 2nd stage:");
	// inflog("Finished 2nd stage successfully");

	printf("------- %s -------\n", filePath);
	for(int i = 0; i < tokens->_length; i++) {
		printf("tok[%d]: '%s'\n", i + 1, (char*)tokens->_array[i]);
		if(tokens->_array[i])
			free(tokens->_array[i]);
	}
	vector_dtor(tokens);

	return 0;
}
