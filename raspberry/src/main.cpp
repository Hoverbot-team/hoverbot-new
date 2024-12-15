#include "sensors/gyro.hpp"
#include <iostream>
#include "wiringSerial.h"
using namespace std;
float mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int main(){
    int serialPort;
    serialPort = serialOpen("/dev/ttyAMA0", 115200);  // Adjust the port and baud rate as needed
    if (serialPort == -1) {
        printf("Unable to open serial port\n");
        return 1;
    }
    
    MPU6050 gyro;
    while(1){
        serialPuts(serialPort, "Hello, UART!\n");
    }
    
}