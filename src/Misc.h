#ifndef _MISC_H_
#define _MISC_H_

#include "Header.h"

void initLogger(int argc, char** argv) {
	char* logname = (char*)malloc(sizeof(char) * 64);
	if(!logname)
		exitWithError(_errcode_log_error, ERRCODE_MEM_MSG);
	snprintf(logname, 64, "./logs/log_%s.log", __TIMESTAMP__);

	initDebugLog(logname);

	free(logname);
}

#endif