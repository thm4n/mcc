#include "Header.h"

int main(int argc, char** argv) {
	char* name = "tamir";
	initLogger(argc, argv);

	nonlog("this is nonlog log test - my name is %s", name);
	errlog("this is errlog log test - my name is %s", name);
	wrnlog("this is wrnlog log test - my name is %s", name);
	inflog("this is inflog log test - my name is %s", name);
	dbglog("this is dbglog log test - my name is %s", name);
	fatlog("this is fatlog log test - my name is %s", name);

	return 0;
}
