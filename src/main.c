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
	

	return 0;
}
