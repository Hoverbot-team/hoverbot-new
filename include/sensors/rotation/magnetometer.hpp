#include <iostream>
#include <wiringPiI2C.h>
#define device_address 0x1E
#define CONFIG_REG_A 0x00
#define CONFIG_REG_B 0x01
#define MODE_REG 0x02
class HMC5883L {
public:
    HMC5883L();
    int16_t readRawX();
    int16_t readRawY();
    int16_t readRawZ();
private:
    int fd; // File descriptor for I2C communication
    int readWord2C(int addr);
    float convertToDegrees(int16_t raw_value);
    int16_t readI2c(int addr);
};