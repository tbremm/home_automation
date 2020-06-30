#include "../../headers/logging.h"

using namespace std;

int test_log () {
    ofstream logfile ("logs/logs.log", ios::out | ios::app);  // Output and append mode
    if (!logfile.is_open()) {
        cout << "Error opening logfile...\n";
        return 1;
    }
    logfile << "Test log\n";
    logfile.close();
    return 0;
}
