#ifndef _MISC_H_
#define _MISC_H_

#include "Header.h"

void initLogger(int argc, char** argv);

int isWS(const char ch);
int isDigit(const char ch);
int isChar(const char ch);
int isSpec(const char ch);

int isValidName(const char* tok);

#endif