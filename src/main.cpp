#include "sensors/gyro.h"
#include <iostream>

using namespace std;
float mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int main(){
    MPU6050 gyro;
    while(1){
        cout << gyro.roll() << endl;
    }
    
}