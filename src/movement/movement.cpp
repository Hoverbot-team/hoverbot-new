#include "movement/movement.hpp"
#include <iostream>
#include <csignal>
using namespace std;

float movement::simpleStability(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
movement::movement(int speedPinLeft, int dirPinLeft, int speedPinRight, int dirPinRight,double pid_kp,double pid_ki,double pid_kd): eng_L(speedPinLeft, dirPinLeft), eng_R(speedPinRight, dirPinRight), pid(pid_kp, pid_ki, pid_kd)
{
    logs.log("initialising movement");
    
    //thread inits
    thread movementLoop(&movement::loop, this);
    movementLoop.detach();
    thread safeLoop(&movement::safe, this);
    safeLoop.detach();
    
}

movement::~movement() {
    eng_L.stop();
    eng_R.stop();
    delayMicroseconds(100);
}

void movement::loop() {
    logs.log("Movement loop starting");
    while (true) {
        int correction = simpleStability(gyro.roll(), -90, 90, 30, -30);
        cout << "Correction: " << correction << endl;
        if (isEnabled) {
            /*
            double correction = pid.calculate(setpoint, gyro.roll());

            int motorLeftSpeed = (baseSpeed - correction) * 2;
            int motorRightSpeed = (baseSpeed + correction) * 2;

            // Clamp to valid -255 to 255 range (optional but safe)
            motorLeftSpeed = std::max(-255, std::min(255, motorLeftSpeed));
            motorRightSpeed = std::max(-255, std::min(255, motorRightSpeed));

            // Convert to 0–100 for softPwm
            int pwmLeft = abs(motorLeftSpeed) * 100 / 255;
            int pwmRight = abs(motorRightSpeed) * 100 / 255;
            */
            // Send to motors — keep your direction logic
            cout << "Gyro Roll: " << gyro.roll() << endl;
            if (correction < 0){
                eng_L.engine_write(abs(correction), true);
                eng_R.engine_write(abs(correction), false);
            } else {
                eng_L.engine_write(abs(correction), false);
                eng_R.engine_write(abs(correction), true);
            }

            // Optional debug
            //cout << motorLeftSpeed << endl;
            //cout << motorRightSpeed << endl;
            //delayMicroseconds(100);
        }
    }

}
void movement::enable() {
    isEnabled = true;
    logs.log("Movement enabled.");
}
void movement::safe(){
    while(abs(movement::gyro.read_gyro_X()) < 60 && abs(movement::gyro.read_gyro_Y()) < 60 && abs(movement::gyro.read_gyro_Z()) < 60){
        //std::cout<< "safe loop running"<<std::endl;    
    }
    eng_L.stop();
    eng_R.stop();
    delayMicroseconds(100);
    logs.log("automatic shutdown event occured");
    exit(0);
    
}
void movement::stop(){
    eng_L.stop();
    eng_R.stop();
    delayMicroseconds(100);
    logs.log("Engines stopped.");
}