#include "movement/engines.hpp"
#include <iostream>
#include <iostream>

#include <thread>  
using namespace std;
Engines::Engines(int Pin, int Dir_pin): pin(Pin), dir(Dir_pin){
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Failed to initialize WiringPi" << std::endl;
    }
    if (softPwmCreate(Pin, 0, 100) != 0) {
        std::cerr << "Failed to initialize soft PWM on pin " << Pin << std::endl;
    }
    pinMode(dir,OUTPUT);
    

}
Engines::~Engines(){
    softPwmWrite(pin, 0);
}
void Engines::engine_write(int speed, bool Direction){
    if(!Stop){
        if(speed >= 100){
            speed = 0;

            }
        if(Direction){
            digitalWrite(dir, LOW);
            cout << "dir change" << endl;

        }
        else{
            digitalWrite(dir, HIGH);
            cout << "dir change" << endl;


        }

        softPwmWrite(pin, speed);
    }else{
        stop();
        cout<<"engines stopped"<<endl;
    }


    
    

}
void Engines::stop(){
    softPwmWrite(pin, 0);

}

