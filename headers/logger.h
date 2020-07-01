#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DEBUG 3

class Logger {
    private:
        std::string log_name;

    public:
        Logger (std::string log_filename);
        void log (int level, std::string msg);
        int test_log ();  // Writes a simple string to the class's log location to test logging
};

#endif  // LOGGER_H_
