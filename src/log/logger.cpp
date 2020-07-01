#include "../../headers/logging.h"

using namespace std;

class Logger {
    Logger (string log_filename) {
        // TODO: Path validation
        log_name = log_filename;
    }

    void log (int level, string msg) {
        // TODO: Accept var args so callers can format string within call
        ofstream logfile (logloc, ios::out | ios::app);  // Output and append mode
        if (!logfile.is_open()) {
            return;
        }
        switch (level):
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

        logfile.close();
        return;
    }

    int test_log (string filename) {
        ofstream logfile ("logs/" + filename, ios::out | ios::app);  // Output and append mode
        if (!logfile.is_open()) {
            cout << "Error opening logfile ./logs/" << filename << "...\n";
            return 1;
        }
        logfile << "Test log success!\n";
        cout << "Successfully logged to ./logs/" << filename << endl;
        logfile.close();
        return 0;
    }
};
