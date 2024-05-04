#include "Error.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "Error.h"

#if DEBUG == true
FILE* logger_fd = NULL;
#endif

const char* getMsgByErrcode(error_code_t errcode);
void initDebugLog(const char* dbg_log);
const char* getMsgStr(msg_t msgtype);

const char* _setColor(char* buff, int ground, int attrib, int color) {
    snprintf(buff, MIN_BUFF_LEN - 1, "\033[%d;%dm", attrib, (ground * 10) + color);
    return buff;
}

const char* getMsgByErrcode(error_code_t errcode) {
	switch(errcode) {
	case _errcode_usage:
		return ERRCODE_USAGE_MSG;

	case _errcode_clean:
		return ERRCODE_CLEAN_MSG;
		
	case _errcode_unknown:
		return ERRCODE_UNKOWN_MSG;
		
	case _errcode_log_error:
		return ERRCODE_LOG_MSG;

	case _errcode_IO:
		return ERRCODE_IO_MSG;
	
	case _errcode_external:
		return ERRCODE_EXT_MSG;

	case _errcode_mem_err:
		return ERRCODE_MEM_MSG;
	}
	return "";
}

void _exitWithError(const char* file, const char* func, unsigned int line, error_code_t errcode, const char* format, ...) {
	char buff[2048] = {0};
	va_list val;
	va_start(val, format);
	snprintf(buff, 2048, "\n  Error Raised:\n  >> %s - %s.\n", getMsgByErrcode(errcode), format);
	vfprintf(stderr, buff, val);
#if DEBUG == true
	if(logger_fd)
		vfprintf(logger_fd, buff, val);
#endif
	_logger_write(file, func, line, msg_t_fatal, buff);
	va_end(val);
	exit(errcode);
}

void setTColorByMsgType(msg_t msgtype) {
	char buff[MIN_BUFF_LEN] = {0};
	switch(msgtype) {
	case msg_t_error:
		fprintf(stderr, "%s", setColor(buff, Red));
		break;
	case msg_t_warning:
		fprintf(stderr, "%s", setColor(buff, Yellow));
		break;
	case msg_t_info:
		fprintf(stderr, "%s", setColor(buff, Green));
		break;
	case msg_t_debug:
		fprintf(stderr, "%s", setColor(buff, Blue));
		break;
	case msg_t_fatal:
		fprintf(stderr, "%s", _setColor(buff, FG, _ATTR_UNDERSCORE, Red));
		break;
	case msg_t_none:
	default:
		fprintf(stderr, "%s", COLOR_RESET);
	}
}

const char* getMsgStr(msg_t msgtype) {
	switch(msgtype) {
	case msg_t_error:
		return "ERROR";
	case msg_t_warning:
		return "WARN";
	case msg_t_info:
		return "INFO";
	case msg_t_debug:
		return "DEBUG";
	case msg_t_fatal:
		return "FATAL";
	case msg_t_none:
		return "***";
	}
	return "UNKNOWN";
}

#if DEBUG == true
#warning "DEBUG MODE ACTIVATED\n"

void initDebugLog(const char* dbg_log) {
	logger_fd = fopen(dbg_log, "w");
	if(!logger_fd)
		exitWithError(_errcode_log_error, "Cant open log file.\n");

	dbglog("Debug log initialized successfully");

	atexit(closeDebugLog);
}

void _logger_write(const char* file, const char* func, unsigned int line, msg_t msgtype, const char* format, ...) {
	va_list val;
	char* buffer = (char*)malloc(sizeof(char) * MAX_BUFF_LEN);
	char* msg = (char*)malloc(sizeof(char) * MAX_BUFF_LEN);

	if(!buffer || !msg) {
		printf("internal logger error: %s\n", ERRCODE_MEM_MSG);
		exit(_errcode_mem_err);
	}

	va_start(val, format);
	setTColorByMsgType(msgtype);
	snprintf(buffer, MAX_BUFF_LEN - 1, " >> %s - %-5s -> %s : %s : %4d - %s\n", __TIME__, getMsgStr(msgtype), file, func, line, format);
	vsnprintf(msg, MAX_BUFF_LEN, buffer, val);
	if(logger_fd)
		fwrite(msg, 1, strlen(msg), logger_fd);
	fwrite(msg, 1, strlen(msg), stderr);
	setTColorByMsgType(msg_t_none);
	va_end(val);

	free(buffer);
	free(msg);
}

void closeDebugLog() {
	fclose(logger_fd);
}

#else

void initDebugLog(const char* dbg_log) {
}

void _logger_write(const char* file, const char* func, unsigned int line, msg_t msgtype, const char* format, ...) {

}

void closeDebugLog() {
}

#endif

#ifdef __cplusplus
}
#endif