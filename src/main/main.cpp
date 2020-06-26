// Top level source file
// Reads temperature data from sensor and displays on the LCD

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>
#include <string>
#include <bits/stdc++.h>
#include <fcntl.h>
#include <iomanip>
#include <sstream>
#include "../../headers/ds18b20_temp_sensor.h"
#include "../../headers/lcd_2004a_i2c.h"

using namespace std;

int main () {
    printf("Beginning program...\n");
    char* sensor_path = "/sys/bus/w1/devices/28-3c01d6073581/w1_slave";
    int gpio_pin = 4;
    int lcd_i2c_address = 0x27;
    int lcd_blen = 1;
    Ds18b20 temp_sensor(gpio_pin, sensor_path);
    lcd_2004a_i2c lcd (lcd_i2c_address, lcd_blen);

    float temperature_c = temp_sensor.get_temp_c();
    float temperature_f = temp_sensor.get_temp_f();

    printf("Converting %f to string...\n", temperature_c);
    stringstream ss_c;
    stringstream ss_f;
    ss_c << "C: " << fixed << setprecision(2) << temperature_c;
    ss_f << "F: " << fixed << setprecision(2) << temperature_f;
    string sc = ss_c.str();
    string sf = ss_f.str();
    int nc = sc.length();
    char c_out[nc + 1];

    int nf = sf.length();
    char f_out[nf + 1];

    strcpy(c_out, sc.c_str());
    cout << sc << "\n";
    strcpy(f_out, sf.c_str());
    cout << sf << "\n";

    lcd.clear();
    lcd.write(0, 0, c_out);
    lcd.write(0, 1, f_out);
    delay(5000);
    lcd.clear();

    return 0;
}
