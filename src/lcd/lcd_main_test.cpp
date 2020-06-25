// Testing the lcd lib
// Make sure to compile/build with -lwiringPi  flag

#include "lcd_2004a_i2c.h"

int main() {
    printf("Instantiating LCD class\n");
    lcd_2004a_i2c lcd (I2C_ADDR, BLEN);
    printf("Writing hello world\n");
    lcd.write(0, 0, "Hello Earth!"); // Gives deprecation warning about conversion from str const to char*
    printf("Delaying...\n");
    delay(5000);
    lcd.clear();
    return 0;
}
