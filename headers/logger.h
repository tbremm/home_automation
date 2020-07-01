#ifndef LOGGING_H_
#define LOGGING_H_

#include <iostream>
#include <fstream>

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DEBUG 3

class Logger {
    private:
        string log_name;

    public:
        Logger (string log_filename);
        void log (int level, string msg); // returns false if logfile can't be opened
        int test_log (string filename);  // Writes a simple string to the given log location to test logging
};

#endif  // LOGGING_H_
