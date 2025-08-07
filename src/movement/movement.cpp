#include "movement/movement.hpp"
#include <iostream>
using namespace std;

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
        if (isEnabled) {
            double correction = pid.calculate(setpoint, gyro.roll());

            int motorLeftSpeed = (baseSpeed - correction) * 2;
            int motorRightSpeed = (baseSpeed + correction) * 2;

            // Clamp to valid -255 to 255 range (optional but safe)
            motorLeftSpeed = std::max(-255, std::min(255, motorLeftSpeed));
            motorRightSpeed = std::max(-255, std::min(255, motorRightSpeed));

            // Convert to 0–100 for softPwm
            int pwmLeft = abs(motorLeftSpeed) * 100 / 255;
            int pwmRight = abs(motorRightSpeed) * 100 / 255;

            // Send to motors — keep your direction logic
            if (correction > 0){
                eng_L.engine_write(pwmLeft, true);
                eng_R.engine_write(pwmRight, false);
            } else {
                eng_L.engine_write(pwmLeft, false);
                eng_R.engine_write(pwmRight, true);
            }

            // Optional debug
            cout << motorLeftSpeed << endl;
            cout << motorRightSpeed << endl;
            delayMicroseconds(100);
        }
    }

}
void movement::enable() {
    isEnabled = true;
    logs.log("Movement enabled.");
}
void movement::safe(){
    while(abs(movement::gyro.read_gyro_X()) < 60 && abs(movement::gyro.read_gyro_Y()) < 60 && abs(movement::gyro.read_gyro_Z()) < 60){
        std::cout<< "safe loop running"<<std::endl;    
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