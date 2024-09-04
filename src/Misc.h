#ifndef _MISC_H_
#define _MISC_H_

#include "Header.h"

#define IS_ALPHA(ch)   ((ch | 0x20) >= 'a' && (ch | 0x20) <= 'z')
#define IS_DIGIT(ch) (ch >= '0' && ch <= '9')

int isAlpha(char ch);
int isDigit(char ch);
int isWhitespace(char ch);
int isAllowedInIdentifier(char ch);
int isAllowedInNumber(char ch);
int isDQuotes(char ch);
int isQuote(char ch);

#endif