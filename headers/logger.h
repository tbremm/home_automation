#ifndef LOGGING_H_
#define LOGGING_H_

#include <iostream>
#include <fstream>

int test_log ();

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DEBUG 3

class Logger {
    private:
        string logloc;

    public:
        bool log (string msg, int level);
};

#endif  // LOGGING_H_
