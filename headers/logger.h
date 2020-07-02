#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

#define LOG_LOCATION "logs/logs.log"

enum class LogLevel {
    error,
    warning,
    info,
    debug
};

class Logger {
    private:
        std::string log_name;

    public:
        Logger (std::string log_filename);
        void log (LogLevel level, std::string msg);
        int test_log ();  // Writes a simple string to the class's log location to test logging
};

std::ostream& operator<<( std::ostream &output, const LogLevel &level );

extern Logger logger;

#endif  // LOGGER_H_
