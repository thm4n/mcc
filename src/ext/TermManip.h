#ifndef _DEFS_H_
#define _DEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DO_HIDE_CURSOR  (printf("\x1b[?25l"))
#define DO_SHOW_CURSOR  (printf("\x1b[?25h"))

#define DO_RETURN_HOME  (printf("\033[0;0H"))
#define DO_COLOR_RESET  (printf("\033[0m"))

#define HIDE_CURSOR  ("\x1b[?25l")
#define SHOW_CURSOR  ("\x1b[?25h")

#define RETURN_HOME  ("\033[0;0H")
#define COLOR_RESET  ("\033[0m")

#define Black  30
#define Red    31
#define Green  32
#define Yellow 33
#define Blue   34
#define Purple 35
#define Cyan   36
#define White  37

#define FG 0
#define BG 1

#define _ATTR_REG        0
#define _ATTR_LIGHT      1
#define _ATTR_DIM        2
#define _ATTR_UNDERSCORE 4
#define _ATTR_BLINK      5
#define _ATTR_REVERSE    7
#define _ATTR_HIDDEN     8

const char* _setColor(char* buff, int ground, int attrib, int color);

#define setColor(buff, color) (_setColor(buff, FG, _ATTR_REG, color))
#define setLightColor(buff, color) (_setColor(buff, FG, _ATTR_LIGHT, color))

#define dropline(index)    (index + DEF_TERM_WIDTH)
#define lineReturn(index)  (index % DEF_TERM_WIDTH)
#define lineDropRet(index) (dropline(lineReturn(index)))

#ifdef __cplusplus
}
#endif

#endif