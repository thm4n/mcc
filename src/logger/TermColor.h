#ifndef _TERM_COLOR_H_
#define _TERM_COLOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define TC_HIDE_CURS ("\x1b[?25l")
#define TC_SHOW_CURS ("\x1b[?25h")

#define TC_GOTO_HOME ("\033[0;0H")
#define TC_RESET_SEQ ("\033[0m")

#define TC_RESET    00
#define TC_BLACK    30
#define TC_RED      31
#define TC_GREEN    32
#define TC_YELLOW   33
#define TC_BLUE     34
#define TC_PURPLE   35
#define TC_CYAN     36
#define TC_WHITE    37

#define TC_ATTR_REGULAR    0
#define TC_ATTR_LIGHT      1
#define TC_ATTR_DIM        2
#define TC_ATTR_UNDERSCORE 4
#define TC_ATTR_BLINK      5
#define TC_ATTR_REVERSE    7
#define TC_ATTR_HIDDEN     8

#define TC_BG 1
#define TC_FG 0

#define TermColor_set(fd, color) (TermColor_set_adv(fd, TC_FG, TC_ATTR_REGULAR, color))

void TermColor_set_adv(FILE* fd, int fg, int attr, int color);

#endif