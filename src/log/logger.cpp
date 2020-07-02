#include "../../headers/logger.h"

using namespace std;

//class Logger {
Logger::Logger (string log_filename) {
    // TODO: Path validation
    log_name = log_filename;
}

void Logger::log (LogLevel level, string msg) {
    // TODO: Accept var args so callers can format string within call
    ofstream logfile (log_name, ios::out | ios::app);  // Output and append mode
    if (!logfile.is_open()) return;

    // Get the current local time to prepend to the log line
    time_t raw_time;
    struct tm* timeinfo;
    char buff[80]; // Size used in cplusplus.com strftime example
    time(&raw_time);
    timeinfo = localtime(&raw_time);
    strftime(buff, 80, "[%D %R] ", timeinfo);

    logfile << buff << level << msg << endl;
    logfile.close();
    return;
}

ostream& operator<<( ostream &output, const LogLevel &level ) {
         switch (level) {
        case LogLevel::error:
            output << "ERROR: ";
            break;
        case LogLevel::warning:
            output << "WARNING: ";
            break;
        case LogLevel::info:
            output << "INFO: ";
            break;
        case LogLevel::debug:
            output << "DEBUG: ";
            break;
        default:
            output << "UNKNOWN LOG LEVEL: ";
            break;
    }
         return output;
}

int Logger::test_log () {
    ofstream logfile ("logs/" + log_name, ios::out | ios::app);  // Output and append mode
    if (!logfile.is_open()) {
        cout << "Error opening logfile ./logs/" << log_name << "...\n";
        return 1;
    }
    logfile << LogLevel::debug << "Test log success!\n";
    cout << "Successfully logged to ./logs/" << log_name << endl;
    logfile.close();
    return 0;
}

// See header file for log location
// TODO - put this in a config file so we don't have to recompile to change the logfile
Logger logger(LOG_LOCATION);
