#include "../../headers/logger.h"

using namespace std;

//class Logger {
Logger::Logger (string log_filename) {
    // TODO: Path validation
    log_name = log_filename;
}

void Logger::log (int level, string msg) {
    // TODO: Accept var args so callers can format string within call
    ofstream logfile (log_name, ios::out | ios::app);  // Output and append mode
    if (!logfile.is_open()) {
        return;
    }
    switch (level) {
        case LOG_LEVEL_ERROR:
            logfile << "ERROR: " << msg << endl;
            break;
        case LOG_LEVEL_WARN:
            logfile << "WARNING: " << msg << endl;
            break;
        case LOG_LEVEL_INFO:
            logfile << "INFO: " << msg << endl;
            break;
        case LOG_LEVEL_DEBUG:
            logfile << "DEBUG: " << msg << endl;
            break;
        default:
            logfile << "UNKNOWN LOG LEVEL (" << level << "): " << msg << endl;
            break;
    }

    logfile.close();
    return;
}

int Logger::test_log () {
    ofstream logfile ("logs/" + log_name, ios::out | ios::app);  // Output and append mode
    if (!logfile.is_open()) {
        cout << "Error opening logfile ./logs/" << log_name << "...\n";
        return 1;
    }
    logfile << "Test log success!\n";
    cout << "Successfully logged to ./logs/" << log_name << endl;
    logfile.close();
    return 0;
}
//};
