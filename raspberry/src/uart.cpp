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
    int i;
    for(i = 0; i <= input.length(); i++){
        serialPutchar(UART::serialPort,input[i]);
    }
}

string UART::read()
{
    string in;
    return in;
}
