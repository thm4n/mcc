#include "TermColor.h"

void TermColor_set_adv(FILE* fd, int fg, int attr, int color) {
    if(color)
        fprintf(fd, "\033[%d;%dm", attr, fg*10 + color);
    else
        fprintf(fd, TC_RESET_SEQ);
}
