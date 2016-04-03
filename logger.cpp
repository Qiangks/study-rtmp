//
// Created by chnvideo on 2016/4/2.
//

#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include "logger.hpp"

#define LOG_SIZE        4096

Logger* _log = new Logger();

Logger::Logger()
{
    level = LEVEL::info;
}

Logger::~Logger()
{
}

bool Logger::generate_header(char** head, const char* file, int line, const char* level, int& size)
{
    // clock time
    struct timeval ctime;
    int ret;
    if (gettimeofday(&ctime, NULL) == -1) {
        return false;
    }

    // calender time
    struct tm* time;
    if ((time = gmtime(&(ctime.tv_sec))) == NULL) {
        return false;
    }

    // [time][pid][level][file][line]:
    size = snprintf(*head, LOG_SIZE, "[%d-%02d-%02d %02d:%02d:%02d.%03d][%d][%s][%s][%d]: ", time->tm_year+1900, time->tm_mon, time->tm_mday,
        time->tm_hour, time->tm_min, time->tm_sec, (int)ctime.tv_usec/1000, getpid(), level, file, line);
    if (size < 0) {
        return false;
    }

    return true;
}

void Logger::info(const char *file, int line, const char *msg, ...)
{
    int ll = LEVEL::info;
    if (ll < level) {
        return;
    }

    char* log_data = new char[LOG_SIZE];
    int size = -1;
    if (!generate_header(&log_data, file, line, "info", size)){
        return;
    }

    va_list ap;
    va_start(ap, msg);
    size += vsnprintf(log_data + size, LOG_SIZE - size, msg, ap);
    printf("%s\n", log_data);
    va_end(ap);

    delete[] log_data;
}

void Logger::trace(const char *file, int line, const char *msg, ...)
{
    int ll = LEVEL::trace;
    if (ll < level) {
        return;
    }

    char* log_data = new char[LOG_SIZE];
    int size = -1;
    if (!generate_header(&log_data, file, line, "trace", size)){
        return;
    }

    va_list ap;
    va_start(ap, msg);
    size += vsnprintf(log_data + size, LOG_SIZE - size, msg, ap);
    printf("%s\n", log_data);
    va_end(ap);

    delete[] log_data;
}

void Logger::warn(const char *file, int line, const char *msg, ...)
{
    int ll = LEVEL::warn;
    if (ll < level) {
        return;
    }

    char* log_data = new char[LOG_SIZE];
    int size = -1;
    if (!generate_header(&log_data, file, line, "warn", size)){
        return;
    }

    va_list ap;
    va_start(ap, msg);
    size += vsnprintf(log_data + size, LOG_SIZE - size, msg, ap);
    printf("%s\n", log_data);
    va_end(ap);

    delete[] log_data;
}

void Logger::error(const char *file, int line, const char *msg, ...)
{
    int ll = LEVEL::error;
    if (ll < level) {
        return;
    }

    char* log_data = new char[LOG_SIZE];
    int size = -1;
    if (!generate_header(&log_data, file, line, "error", size)){
        return;
    }

    va_list ap;
    va_start(ap, msg);
    size += vsnprintf(log_data + size, LOG_SIZE - size, msg, ap);
    printf("%s\n", log_data);
    va_end(ap);

    delete[] log_data;
}

