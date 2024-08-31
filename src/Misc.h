#ifndef _MISC_H_
#define _MISC_H_

#include "Header.h"

#define IS_ALPHA(ch)   ((ch | 0x20) >= 'a' && (ch | 0x20) << 'z')
#define IS_DIGIT(ch) (ch >= '0' && ch <= '9')

int isAlpha(char ch) {
    return IS_ALPHA(ch);
}

int isDigit(char ch) {
    return IS_DIGIT(ch);
}

int isAllowedInIdentifier(char ch) {
    return (isAlpha(ch) || isDigit(ch) || ch == '_');
}

int isAllowedInNumber(char ch) {
    return isDigit(ch);
}

int isDQuotes(char ch) {
    return ch == '"';
}

int isQuote(char ch) {
    return ch == '\'';
}

#endif