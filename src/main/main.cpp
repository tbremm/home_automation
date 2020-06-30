// Top level source file
// Reads temperature data from sensor and displays on the LCD

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <glob.h>
#include <vector>
#include "../../headers/ds18b20_temp_sensor.h"
#include "../../headers/lcd_2004a_i2c.h"

using namespace std;

char const* format_float (string prefix, int precision, float f);
int get_sensor_names (vector<char*>* sensor_paths);

int main () {
    printf("Beginning program...\n");

    int lcd_i2c_address = 0x27;
    int lcd_blen = 1;
    float temperature_c = 0.0;
    float temperature_f = 0.0;
    int gpio_pin = 0;
    int sensor_err = 0;
    vector<char*> sensor_paths;
    vector<Ds18b20> sensors;

    // Get the list of sensor device paths
    sensor_err = get_sensor_names (&sensor_paths);
    if (sensor_err != 0 || sensor_paths.size() == 0) {
        printf("Could not find any sensors, quitting...\n");
        return sensor_err;
    }

    printf("Found %d sensors.\n", sensor_paths.size());

    // Get GPIO pin for each sensor and create a new sensor object for each
    for (unsigned int i = 0; i < sensor_paths.size(); i++) {
        printf("Enter GPIO pin for sensor: %s\n", sensor_paths[i]);
        cin >> gpio_pin;
        Ds18b20 sensor(gpio_pin, sensor_paths[i]);
        sensors.push_back(sensor);
    }

    // Init the LCD
    lcd_2004a_i2c lcd (lcd_i2c_address, lcd_blen);
    lcd.clear();

    while(true) {
        for (unsigned int i = 0; i < sensors.size(); i++) {
            temperature_c = sensors[i].get_temp_c();
            delay(3000);  // Forum says the sensor needs ~750ms between reads
            temperature_f = sensors[i].get_temp_f();
            string strSensorNum = to_string(i);
            char const* chSensorNum = strSensorNum.c_str();
            sensors[i].print_temp_c();
            sensors[i].print_temp_f();
            lcd.clear();
            lcd.write(0, 0,"Sensor #");
            lcd.write(8, 0, chSensorNum);
            lcd.write(0, 1, format_float("C: ", 2, temperature_c));
            lcd.write(0, 2, format_float("F: ", 2, temperature_f));
        }
    }
    lcd.clear();
    return 0;
}

char const* format_float (string prefix, int precision, float f) {
    stringstream ss;
    ss << prefix << fixed << setprecision(precision) << f;
    string str = ss.str();
    int n = str.length();
    char* c_out = new char[n + 1];
    strcpy(c_out, str.c_str());
    return c_out;
}

// Puts a list of sensor device paths into sensor_paths
// Expects sensors to be located in /sys/bus/w1/devices/28-*
int get_sensor_names (vector<char*>* sensor_paths) {
    glob_t globbuf;

    // Find all matching paths
    if (glob("/sys/bus/w1/devices/28-*/w1_slave", 0, NULL, &globbuf) == GLOB_NOMATCH) {
        printf("Could not find any sensors using glob...\n");
        return -1;
    }

    // Push into paths vector
    int num_paths = static_cast<int>(globbuf.gl_pathc);
    for (int i = 0; i < num_paths; i++) {
        (*sensor_paths).push_back(globbuf.gl_pathv[i]);
    }
    return 0;
}
