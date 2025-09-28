#ifndef ENGINES_H
#define ENGINES_H
#include <wiringPi.h>
#include <softPwm.h>
#include <thread>
#include <iostream>
#include <csignal>
class Engines{
    public:
        bool Stop =false;
       Engines(int Pin,int Dir_pin,int max_PWM);
       ~Engines();
       void engine_write(int speed,bool Direction);//0-100 engine power, forward is false backward is true
       void stop();
    private:
        int pin;
        int dir;
        int max_PWM = 100;
    
};
#endif