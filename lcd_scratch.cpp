// Scratch program to explore serial comms with an LCD screen

#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>

using namespace std;		// No need to keep using “std”

int main() {
    printf("Starting program...\n");
    const char* device = "/dev/tty1";
    int baud = 115200;
    int dev_fd = serialOpen(device, baud);
    if (dev_fd < 0) {
        printf("Could not open serial device: %d\n", errno);
        return 1;
    }
    printf("dev_fd: %d\n", dev_fd);
    if (wiringPiSetup() == -1) {  // Setup the library
        printf("Unable to start wiringPi: %d\n", errno);
        return 1;
    }
    serialPrintf(dev_fd, "Test string\n");

//   serialPutchar(dev_fd, 0x7C);
//    serialPutchar(dev_fd, 0x04);
//    serialPuts(dev_fd, "|\\d");
    delay(60000);
    printf("Printed message\n");
    serialClose(dev_fd);
	return 0;
}
