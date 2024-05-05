#include "Misc.h"

void initLogger(int argc, char** argv) {
	char* logname = (char*)malloc(sizeof(char) * 64);
	if(!logname)
		exitWithError(_errcode_log_error, ERRCODE_MEM_MSG);
	snprintf(logname, 64, "./logs/log_%s.log", __TIMESTAMP__);

	initDebugLog(logname);

	free(logname);
}

int isWS(const char ch) {
	return (ch == 0x20 ||
			ch == 0x0A ||
			ch == 0x09 ||
			ch == 0x0D );
}

int isDigit(const char ch) {
	return (ch >= 0x30 && ch <= 0x39);
}

int isChar(const char ch) {
	return ((ch | 32) >= 'a' && (ch | 32) <= 'z') || ch == '_';
}

int isSpec(const char ch) {
	return (ch == '(' || ch == ')' ||
			ch == '[' || ch == ']' ||
			ch == '{' || ch == '}' ||
			ch == '<' || ch == '>' ||
			ch == '!' || ch == '#' ||
			ch == '%' || ch == '^' ||
			ch == '&' || ch == '*' ||
			ch == '-' || ch == '/' ||
			ch == '+' || ch == '=' ||
			ch == '?' || ch == ':' ||
			ch == '~' || ch == '"' ||
			ch == ';' || ch == ',' ||
			ch == '\\' || ch == '\'');
}

int isValidName(const char* tok) {
	int len = 0;

	if(!tok)
		return false;

	len = strlen(tok);
	if(!len) 
		return false;

	if(isDigit(tok[0]) || isSpec(tok[0]))
		return false;

	for(int i = 1; i < len; i++) {
		if(!isChar(tok[i]) && !isDigit(tok[i]))
			return false;
	}

	return true;
}
