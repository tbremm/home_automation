// Class for communicating with a SunFoundry 2004A LCD via I2C backpack

#ifndef LCD_2004A_I2C_H_
#define LCD_2004A_I2C_H_

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <string.h>

// Typical values
#define I2C_ADDR 0x27
#define BLEN 1

class lcd_2004a_i2c {
    private:
        int i2c_addr;   // Hex addr of the LCD, typically 0x27 for 2004A
        int blen;       // Need to figure out what this is for
        int device_fd;  // FD for the I2C device
        
        void init();
        void write_word(int data);
        void send_command(int comm);
        void send_data(int data);
        
    public:
        lcd_2004a_i2c(int i2c_address, int blen);
        void clear();
        void write(int x, int y, char data[]);
};

#endif
