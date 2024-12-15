#include "uart.hpp"
#include "wiringSerial.h"
UART::UART(int baud){
    UART::serialPort = serialOpen("/dev/ttyAMA0", baud);
    if (serialPort == -1) {
        cerr << "Unable to open serial port";
    }
}
void UART::write(string input)
{
}

string UART::read()
{
    string in;
    return in;
}
