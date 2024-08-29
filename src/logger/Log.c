#include "Log.h"

FILE* logger_fd = NULL;

void setTermColorByLogLevel(FILE* fd, enum LOG_LEVEL loglevel) {
    switch(loglevel) {
    case LOG_ERROR:
        TermColor_set(fd, TC_RED);
        break;
    case LOG_WARNING:
        TermColor_set(fd, TC_YELLOW);
        break;
    case LOG_INFO:
        TermColor_set(fd, TC_GREEN);
        break;
    case LOG_DEBUG:
        TermColor_set(fd, TC_BLUE);
        break;
    case LOG_OFF:
    default:
        TermColor_set(fd, TC_RESET);
    }
}

const char* getMsgStr(enum LOG_LEVEL loglevel) {
    switch(loglevel) {
    case LOG_ERROR:
        return "ERROR";
    case LOG_WARNING:
        return "WARN";
    case LOG_INFO:
        return "INFO";
    case LOG_DEBUG:
        return "DEBUG";
    case LOG_OFF:
    default:
        return "***";
    }
}

void _logger_write(const char* file, const char* func, unsigned int line, enum LOG_LEVEL loglevel, const char* format, ...) {
    va_list val;
    char msg[1024] = {0};

    va_start(val, format);
    vsnprintf(msg, 1024, format, val);
    msg[1023] = '\0';
    va_end(val);

    if(logger_fd) {
        fprintf(logger_fd, " >> %-5s - %-40s:%-24s:%d - %s\n", getMsgStr(loglevel), file, func, line, msg);
    }
    else if(DEBUG) {
        setTermColorByLogLevel(stdout, loglevel);
        fprintf(stdout, " >> %-5s - %-40s:%-24s:%d - %s\n", getMsgStr(loglevel), file, func, line, msg);
        setTermColorByLogLevel(stdout, LOG_OFF);
    }
}

void initDebugLog(const char* logPath) {
    logger_fd = fopen(logPath, "w");
    fclose(logger_fd);
}
