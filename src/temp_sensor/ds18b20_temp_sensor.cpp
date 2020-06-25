// Implementation of the ds18b20 temperature sensor functionality


#include "../../headers/ds18b20_temp_sensor.h"

Ds18b20::Ds18b20 (int gpio, char* sensor_path) {
    gpio_pin = gpio;
    sensor_file_path = sensor_path;
    temperature_c = 0.0;
    temperature_f = 0.0;
    
    memset(temperature_raw, 0, sizeof(temperature_raw));
    memset(read_buff, 0, sizeof(read_buff));
    return;
}

int Ds18b20::read_raw_temp () {
    FILE* sensor_fd = fopen(sensor_file_path,"r");
    if (sensor_fd == NULL) {
        printf("\nfopen Error, could not open sensor file\n\n");
        return 1;
    }
    if(fread(read_buff, TEMP_DATA_SIZE_BYTES, NUM_READ_ELEMENTS, sensor_fd) != TEMP_DATA_SIZE_BYTES * NUM_READ_ELEMENTS) {
        printf("\nfread() failed\n\n");
        return 1;
    }
    
    // Extract raw temp bytes
    temperature_raw[0] = read_buff[69];
    temperature_raw[1] = read_buff[70];
    temperature_raw[2] = read_buff[71];
    temperature_raw[3] = read_buff[72];
    temperature_raw[4] = read_buff[73];
    temperature_raw[5] = read_buff[74];
    
    return 0;
}

float Ds18b20::get_temp_c () {
    if (read_raw_temp() != 0) {
        printf("Error getting raw temperature.\n");
        return 1;
    }
    return atoi(temperature_raw) / 1000.0;
}

float Ds18b20::get_temp_f () {
    // get_temp_c handles getting the raw temp, which is natively in celsius
    return (get_temp_c() / 5.0) * 9 + 32;
}

void Ds18b20::print_temp_c () {
    printf("%2.3f", get_temp_c());
    return;
}

void Ds18b20::print_temp_f () {
    printf("%2.3f", get_temp_f());
    return;
}
        
