// Testing the lcd lib
// Make sure to compile/build with -lwiringPi  flag

#include "lcd_2004a_i2c.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Instantiating LCD class");
    lcd_2004a_i2c lcd (0x27, 1);
    printf("Writing hello world");
    lcd.write(0, 0, "Hello Earth!");
    printf("Delaying...");
    delay(10000);
    lcd.clear();
    return 0;
}
