#include "sensors/gyro.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "movement/engines.hpp"
#include "movement/PID.hpp"
#include <thread>
#include "movement/movement.hpp"
#include "modules/codePlugins/loader.hpp"
using namespace std;
//global variables
MPU6050 gyro;
Engines eng_L(12,5);
Engines eng_R(13,6);

float mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void safe(){
    while(abs(gyro.read_gaccel_X()) < 60){
        
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
    auto mods = loadMods("/home/a/plugins/");
    for (auto& mod : mods) {
        mod.instance->onUpdate(0.016f); // fake delta time
    }
    /*
    atexit(onExit);
    thread safety(safe); //activate safety system
    safety.detach();
    double setpoint = 0;    // Target angle 
    PID pid(0.6, 0.002, 0);
    while(1){
        int baseSpeed = 0;
        double correction = pid.calculate(setpoint, gyro.roll());
        int motorLeftSpeed = (baseSpeed - correction)*2;
        int motorRightSpeed = (baseSpeed + correction)*2;

        if (correction > 0){
            eng_L.engine_write(abs(motorLeftSpeed),true);
            eng_R.engine_write(abs(motorRightSpeed),false);
            cout<< motorLeftSpeed << endl; 
            cout <<  motorRightSpeed <<endl;

        }
        else{
            eng_L.engine_write(abs(motorLeftSpeed),false);
            eng_R.engine_write(abs(motorRightSpeed),true);
            cout<< motorLeftSpeed << endl; 
            cout <<  motorRightSpeed <<endl;
        }  
        delayMicroseconds(10);
    }
    */
}