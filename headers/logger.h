#ifndef LOGGER_H_
#define LOGGER_H_

// Class to aid in logging data to a log file

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

const std::string LOG_LOCATION ("logs/logs.log");  // Change this to update the logfile location

// Levels of log verbosity/severity
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
        int test_log ();  // Writes a simple string to the given log location to test logging
};

std::ostream& operator<<( std::ostream &output, const LogLevel &level );

extern Logger logger;

#endif  // LOGGER_H_
