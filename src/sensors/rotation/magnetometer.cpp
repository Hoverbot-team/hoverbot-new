#include "sensors/rotation/magnetometer.hpp"
 HMC5883L::HMC5883L() {
    fd = wiringPiI2CSetup(device_address); // Initialize I2C communication with the device address
    wiringPiI2CWriteReg8(fd, MODE_REG, 0x00); // Set to continuous mode
    wiringPiI2CWriteReg8(fd, CONFIG_REG_A, 0x70);
    wiringPiI2CWriteReg8(fd, CONFIG_REG_B, 0xA0); // Set gain
}
