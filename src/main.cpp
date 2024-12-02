#include "gyro.h"
#include <iostream>

using namespace std;
int main(){
    MPU6050 gyro;
    while(1){
        cout << gyro.roll() << endl;
    }
    
}