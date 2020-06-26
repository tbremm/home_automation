// Top level source file
// Reads temperature data from sensor and displays on the LCD

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include <fcntl.h>
#include "../../headers/ds18b20_temp_sensor.h"
#include "../../headers/lcd_2004a_i2c.h"


int main () {
    printf("Beginning program...\n");
    char* sensor_path = "/sys/bus/w1/devices/28-3c01d6073581/w1_slave";
    int gpio_pin = 4;
    int lcd_i2c_address = 0x27;
    int lcd_blen = 1;
//    Ds18b20 temp_sensor(gpio_pin, sensor_path);
    lcd_2004a_i2c lcd (lcd_i2c_address, lcd_blen);

    lcd.clear();
    lcd.write(0, 0, "Hello world!");
    delay(5000);
    lcd.clear();

    return 0;
}
