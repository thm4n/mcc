#include "Misc.h"

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
