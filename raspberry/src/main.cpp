#include "sensors/gyro.hpp"
#include <iostream>
#include "uart.hpp"
using namespace std;
float mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int main(){


    UART uart(115200);
    MPU6050 gyro;
    while(1){
    }
    
}