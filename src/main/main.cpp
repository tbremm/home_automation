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

char* format_float (string prefix, int precision, float f);
char* get_sensor_name ();

int main () {
    printf("Beginning program...\n");
    char* sensor_path = "/sys/bus/w1/devices/28-3c01d6073581/w1_slave";
    int gpio_pin = 4;
    int lcd_i2c_address = 0x27;
    int lcd_blen = 1;
    float temperature_c = 0.0;
    float temperature_f = 0.0;
    Ds18b20 temp_sensor(gpio_pin, sensor_path);
    lcd_2004a_i2c lcd (lcd_i2c_address, lcd_blen);

    while(true) {
        temperature_c = temp_sensor.get_temp_c();
        temperature_f = temp_sensor.get_temp_f();
        lcd.clear();
        lcd.write(0, 0, format_float("C: ", 2, temperature_c));
        lcd.write(0, 1, format_float("F: ", 2, temperature_f));
        temp_sensor.print_temp_c();
        temp_sensor.print_temp_f();
        delay(1000);
    }
    lcd.clear();
    return 0;
}

char* format_float (string prefix, int precision, float f) {
    stringstream ss;
    ss << prefix << fixed << setprecision(precision) << f;
    string str = ss.str();
    int n = str.length();
    char* c_out = new char[n + 1];
    strcpy(c_out, str.c_str());
    return c_out;
}
