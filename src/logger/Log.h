#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "TermColor.h"
#include "Defines.h"

enum LOG_LEVEL {
    LOG_OFF,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG
};

enum ERROR_CODES {
    SUCCESS = 0,
    ERRCODE_ALLOC,
    ERRCODE_IO,
    ERRCODE_USAGE,
};

#define wlog(msg_type, format, ...) \
    (_logger_write(__FILE__, __FUNCTION__, __LINE__, msg_type, format __VA_OPT__(,) __VA_ARGS__))

#define errlog(format, ...) \
    (_logger_write(__FILE__, __FUNCTION__, __LINE__, LOG_ERROR, format __VA_OPT__(,) __VA_ARGS__))
#define warlog(format, ...) \
    (_logger_write(__FILE__, __FUNCTION__, __LINE__, LOG_WARNING, format __VA_OPT__(,) __VA_ARGS__))
#define inflog(format, ...) \
    (_logger_write(__FILE__, __FUNCTION__, __LINE__, LOG_INFO, format __VA_OPT__(,) __VA_ARGS__))
#define dbglog(format, ...) \
    (_logger_write(__FILE__, __FUNCTION__, __LINE__, LOG_DEBUG, format __VA_OPT__(,) __VA_ARGS__))

void _logger_write(const char* file, const char* func, unsigned int line, enum LOG_LEVEL loglevel, const char* format, ...);

void initDebugLog(const char* logPath);
void closeDebugLog();

#endif
