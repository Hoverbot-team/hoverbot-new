#include "interfaces/UART/UART.hpp"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdexcept>
#include <cstring>
Uart::Uart(const std::string& device, int baudRate) {
    if (wiringPiSetup() == -1) {
        throw std::runtime_error("Failed to initialize WiringPi");
    }

    fd = serialOpen(device.c_str(), baudRate);
    if (fd < 0) {
        throw std::runtime_error("Failed to open UART device: " + std::string(strerror(errno)));
    }
}

Uart::~Uart() {
    if (fd >= 0) {
        serialClose(fd);
    }
}

void Uart::writeByte(uint8_t byte) {
    serialPutchar(fd, byte);
}

void Uart::writeBytes(const uint8_t* data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        serialPutchar(fd, data[i]);
    }
}

bool Uart::available() const {
    return serialDataAvail(fd) > 0;
}

uint8_t Uart::readByte() {
    return static_cast<uint8_t>(serialGetchar(fd));
}