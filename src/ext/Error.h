#ifndef _ERROR_H_
#define _ERROR_H_

#include "TermManip.h"

#include "Defines.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

#define MAX_BUFF_LEN 256
#define MIN_BUFF_LEN 16

#define wlog(mtype, format, ...) \
		(_logger_write(__FILE__, __FUNCTION__, __LINE__, mtype, format __VA_OPT__(,) __VA_ARGS__))
#define exitWithError(errcode, format, ...) \
		(_exitWithError(__FILE__, __FUNCTION__, __LINE__, errcode, format __VA_OPT__(,) __VA_ARGS__))

#define nonlog(format, ...) \
		(_logger_write(__FILE__, __FUNCTION__, __LINE__, msg_t_none, format __VA_OPT__(,) __VA_ARGS__))
#define errlog(format, ...) \
		(_logger_write(__FILE__, __FUNCTION__, __LINE__, msg_t_error, format __VA_OPT__(,) __VA_ARGS__))
#define wrnlog(format, ...) \
		(_logger_write(__FILE__, __FUNCTION__, __LINE__, msg_t_warning, format __VA_OPT__(,) __VA_ARGS__))
#define inflog(format, ...) \
		(_logger_write(__FILE__, __FUNCTION__, __LINE__, msg_t_info, format __VA_OPT__(,) __VA_ARGS__))
#define dbglog(format, ...) \
		(_logger_write(__FILE__, __FUNCTION__, __LINE__, msg_t_debug, format __VA_OPT__(,) __VA_ARGS__))
#define fatlog(format, ...) \
		(_logger_write(__FILE__, __FUNCTION__, __LINE__, msg_t_fatal, format __VA_OPT__(,) __VA_ARGS__))

typedef enum msg_t {
	msg_t_none    = 0,
	msg_t_error   = 1,
	msg_t_warning = 2,
	msg_t_info    = 3,
	msg_t_debug   = 4,
	msg_t_fatal   = 5,
} msg_t;

typedef enum error_code_t {
	_errcode_clean     = 0,
	_errcode_unknown   = 1,
	_errcode_log_error = 2,
	_errcode_usage     = 3,
	_errcode_IO        = 4,
	_errcode_external  = 5,
	_errcode_mem_err   = 6,
} error_code_t;

#define ERRCODE_CLEAN_MSG  ""
#define ERRCODE_UNKOWN_MSG "Unknown error raised"
#define ERRCODE_LOG_MSG    "Logger Error raised"
#define ERRCODE_USAGE_MSG  "Invalid Usage"
#define ERRCODE_IO_MSG     "File IO error"
#define ERRCODE_EXT_MSG    "External error"
#define ERRCODE_MEM_MSG    "Memory error"

void _exitWithError(const char* file, const char* func, unsigned int line, error_code_t errcode, const char* format, ...);
void _logger_write(const char* file, const char* func, unsigned int line, msg_t msgtype, const char* format, ...);

void initDebugLog(const char* dbg_log);
void closeDebugLog();

#ifdef __cplusplus
}
#endif

#endif