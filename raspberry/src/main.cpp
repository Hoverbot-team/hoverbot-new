#include "sensors/gyro.hpp"
#include <iostream>
#include "uart.hpp"
#include <opencv2/opencv.hpp>
#include "navigation/navVideo.hpp"
#include "movement/engines.hpp"
#include "movement/PID.hpp"
#include <thread>
using namespace std;
//global variables
UART uart(115200);
MPU6050 gyro;
Engines eng_L(12,5);
Engines eng_R(13,6);

float mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void checkArduinoConnection(){
    string in = uart.read();
    while(in != "rr"){
        in = uart.read();
        cout << "no connection" << endl;
    }
    uart.write("ar");
    cout << "connection established" << endl;
}
void safe(){
    while(abs(gyro.read_gaccel_X()) < 40){
        
    }
    eng_L.Stop = true;
    eng_R.Stop = true;
    cout<<"automatic shutdown event occured"<<endl;
    exit(0);
    
}
void onExit() {
    eng_L.stop();
    eng_R.stop();
}

int main(){
    atexit(onExit);
    thread safety(safe); //activate safety system
    safety.detach();
    double setpoint = 0;    // Target angle 
    PID pid(0.6, 0.002, 0.00000000001);


    /*
    cv::VideoCapture camera_cap(0);
    if (!camera_cap.isOpened()) {
        std::cerr << "Error: Could not open the camera!" << std::endl;
        return -1;
    }
    vidGuidance VidGuidance(camera_cap);
    */

    //checkArduinoConnection();
    while(1){
        int baseSpeed = 0;
        double correction = pid.calculate(setpoint, gyro.roll());
        int motorLeftSpeed = (baseSpeed - correction)*2;
        int motorRightSpeed = (baseSpeed + correction)*2;

        if (correction > 0){
            eng_L.engine_write(abs(motorLeftSpeed),true);
            eng_R.engine_write(abs(motorRightSpeed),false);
            //cout<< motorLeftSpeed << endl; 
            //cout <<  motorRightSpeed <<endl;

        }
        else{
            eng_L.engine_write(abs(motorLeftSpeed),false);
            eng_R.engine_write(abs(motorRightSpeed),true);
            //cout<< motorLeftSpeed << endl; 
            //cout <<  motorRightSpeed <<endl;
        }  
        delayMicroseconds(10);
    }
    
}