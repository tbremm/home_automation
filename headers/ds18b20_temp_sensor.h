// Class to represent a temperature sensor object.
// This expects the DS18B20 temperature sensor.
// Need resistor between data and RPi 3.3v VCC (works with 2x2K in series)

#ifndef DS18B20_TEMP_SENSOR_H_
#define DS18B20_TEMP_SENSOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include <fcntl.h>

#define TEMP_DATA_SIZE_BYTES 1  // Size of read data element (1 == byte aka char)
#define NUM_READ_ELEMENTS 74    // Number of elements in sensor read data
#define SIZE_RAW_TEMP 5         // Number of digits in raw temp value
#define READ_BUFF_SIZE 100      // Size of the read buffer (aka num of chars to read, need to see exactly how many this is)

class Ds18b20 {
    private:
        int gpio_pin;                           // GPIO pin sensor is connected to
        char* sensor_file_path;                 // Path to sensor on filesystem
        float temperature_c;                    // Temperature in celsius
        float temperature_f;                    // Temperature in farenheit
        char temperature_raw[SIZE_RAW_TEMP];    // Raw temperature from sensor
        char read_buff[READ_BUFF_SIZE];         // Buffer into which the sensor data will be read from sensor_file

        int read_raw_temp ();                   // Get the raw temp from the sensor and store in temperature_raw

    public:
        Ds18b20 (int gpio, char* sensor_path);  // Constructor
        float get_temp_c ();                    // Returns the temp in Celsius
        float get_temp_f ();                    // Returns the temp in Farenheit
        void print_temp_c ();                   // Prints the temp in C
        void print_temp_f ();                   // Prints the temp in F
};

#endif  // DS18B20_TEMP_SENSOR_H_
