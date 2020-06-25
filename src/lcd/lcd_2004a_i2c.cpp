// Implementation of the lcd_2004a_i2c class

// This uses the 2004A I2C LCD from SunFounder.
// See link below for config guide:
// https://www.sunfounder.com/learn/sensor-kit-v2-0-for-raspberry-pi-b-plus/lesson-30-i2c-lcd1602-sensor-kit-v2-0-for-b-plus.html

// Ensure the jumper is attached on the LCD backpack before connecting power
// or the RPi will turn off!

// Default I2C address is 0x27
// Run "i2cdetect -y 1" in the terminal to see the I2C device

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <string.h>
#include "lcd_2004a_i2c.h"

lcd_2004a_i2c::lcd_2004a_i2c(int in_i2c_address, int in_blen) {
    i2c_addr = in_i2c_address;
    blen = in_blen;
    device_fd = wiringPiI2CSetup(i2c_addr);
    init();
}

void lcd_2004a_i2c::init(){
	send_command(0x33);	// Must initialize to 8-line mode at first
	delay(5);
	send_command(0x32);	// Then initialize to 4-line mode
	delay(5);
	send_command(0x28);	// 2 Lines & 5*7 dots
	delay(5);
	send_command(0x0C);	// Enable display without cursor
	delay(5);
	send_command(0x01);	// Clear Screen
	wiringPiI2CWrite(device_fd, 0x08);
}

void lcd_2004a_i2c::write_word(int data){
	int temp = data;
	if ( blen == 1 )
		temp |= 0x08;
	else
		temp &= 0xF7;
	wiringPiI2CWrite(device_fd, temp);
}

void lcd_2004a_i2c::send_command(int comm){
	int buf;
	// Send bit7-4 firstly
	buf = comm & 0xF0;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (comm & 0x0F) << 4;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

void lcd_2004a_i2c::send_data(int data){
	int buf;
	// Send bit7-4 firstly
	buf = data & 0xF0;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (data & 0x0F) << 4;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

void lcd_2004a_i2c::clear(){
	send_command(0x01);	//clear Screen
}

void lcd_2004a_i2c::write(int x, int y, char data[]){
	int addr, i;
	int tmp;
	if (x < 0)  x = 0;
	if (x > 15) x = 15;
	if (y < 0)  y = 0;
	if (y > 1)  y = 1;

	// Move cursor
	addr = 0x80 + 0x40 * y + x;
	send_command(addr);
	
	tmp = strlen(data);
	for (i = 0; i < tmp; i++){
		send_data(data[i]);
	}
}
