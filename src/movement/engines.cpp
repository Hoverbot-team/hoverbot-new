#include "movement/engines.hpp"
#include <iostream>
#include <iostream>

#include <thread>  
using namespace std;
Engines::Engines(int Pin, int Dir_pin): pin(Pin), dir(Dir_pin){
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Failed to initialize WiringPi" << std::endl;
    }
    pinMode(dir, OUTPUT);
    digitalWrite(dir, LOW); // Set direction to safe default
    if (softPwmCreate(Pin, 0, 100) != 0) {
        std::cerr << "Failed to initialize soft PWM on pin " << Pin << std::endl;
    }
    softPwmWrite(pin, 0); // Ensure PWM is 0 at startup
    
}
Engines::~Engines(){
    softPwmWrite(pin, 0);
}
void Engines::engine_write(int speed, bool Direction){
    if(!Stop){
        speed = std::max(0, std::min(95, speed));

        // Set direction pin before PWM
        if(Direction){
            digitalWrite(dir, LOW);
        }
        else{
            digitalWrite(dir, HIGH);
        }

        softPwmWrite(pin, speed);
        // Debug output
        std::cout << "[Engine] PWM: " << speed << ", Dir: " << (Direction ? "LOW" : "HIGH") << std::endl;
    }else{
        stop();
        cout<<"engines stopped"<<endl;
    }


    
    

}
void Engines::stop(){
    softPwmWrite(pin, 0);

}

