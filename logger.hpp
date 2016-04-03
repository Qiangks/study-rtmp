//
// Created by chnvideo on 2016/4/2.
//

#ifndef RTMP_SERVER_LOGGER_HPP
#define RTMP_SERVER_LOGGER_HPP

#include <stdio.h>

class Logger;

extern Logger* _log;

#define log_info(msg, ...)    _log->info( __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define log_trace(msg, ...)    _log->trace( __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define log_warn(msg, ...)    _log->warn( __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define log_error(msg, ...)    _log->error( __FILE__, __LINE__, msg, ##__VA_ARGS__)

class LEVEL{
public:
    static const int info = 0x01;
    static const int trace = 0x02;
    static const int warn = 0x03;
    static const int error = 0x04;
};

class Logger{
private:
    int pid;
    int level;
public:
    Logger();
    virtual ~Logger();
public:
    bool generate_header(char** head, const char* file, int line, const char* level, int& size);
public:
    void info(const char *file, int line, const char* msg, ...);
    void trace(const char *file, int line, const char* msg, ...);
    void warn(const char *file, int line, const char* msg, ...);
    void error(const char *file, int line, const char* msg, ...);
};

#endif //RTMP_SERVER_LOGGER_HPP
