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
}

void movement::loop() {
    logs.log("Movement loop starting");
    while (true) {
        if (isEnabled) {
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

}
void movement::enable() {
    isEnabled = true;
    logs.log("Movement enabled.");
}
void movement::safe(){
    while(abs(movement::gyro.read_gyro_X()) < 60){
        
    }
    eng_L.stop();
    eng_R.stop();
    logs.log("automatic shutdown event occured");
    exit(0);
    
}
void movement::stop(){
    eng_L.stop();
    eng_R.stop();
    logs.log("Engines stopped.");
}