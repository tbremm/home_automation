// Interfacing with the DS18B20 temperature sensor
// Code inspired by https://www.raspberrypi.org/forums/viewtopic.php?t=70709

// Expects the sensor data pin to be connected to GPIO #4
// Need resistor between data and 3.3v VCC (works with 2x2K in series)

// Adding comment to test git cred storage - DELETE THIS LINE

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include <fcntl.h>

#define SIZE 1
#define NUMELEM 74

using namespace std;

int main ()
{
	FILE *fp = NULL;
	char buff[100];
	char temp_raw[5];
    float temp_c = 0;
    float temp_f = 0;
	memset(buff,0,sizeof(buff));
    const char* file_sensor = "/sys/bus/w1/devices/28-3c01d6073581/w1_slave";

    while(true) {
        
        fp = fopen(file_sensor,"r");

        if (NULL == fp) {
            printf("\nfopen Error, could not open sensor file\n\n");
            return 1;
        }

        if(SIZE*NUMELEM != fread(buff,SIZE,NUMELEM,fp)) {
            printf("\nfread() failed\n\n");
            return 1;
        }

        temp_raw[0] = buff[69];
        temp_raw[1] = buff[70];
        temp_raw[2] = buff[71];
        temp_raw[3] = buff[72];
        temp_raw[4] = buff[73];
        temp_raw[5] = buff[74];
        
        temp_c = atoi(temp_raw) / 1000.0;
        temp_f = (temp_c / 5.0) * 9 + 32;

        printf("Temp:\t%2.3f C\t%2.3f F\n", temp_c, temp_f);
        delay(500);

    }
	return 0;
}
