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

void Uart::write(const std::string& data) {
    serialPuts(fd, data.c_str());
}

bool Uart::available() const {
    return serialDataAvail(fd) > 0;
}

char Uart::readChar() {
    return serialGetchar(fd);
}

std::string Uart::readLine() {
    std::string line;
    while (available()) {
        char c = readChar();
        if (c == '\n') break;
        line += c;
    }
    return line;
}
