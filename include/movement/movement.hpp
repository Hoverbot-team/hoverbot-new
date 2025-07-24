#include <sensors/rotation/gyro.hpp>
#include <movement/engines.hpp>
#include <movement/PID.hpp>
#include <thread>
#include <iostream>
#include "misc/logs/log.hpp"

class movement {
    public:
        movement(int speedPinLeft, int dirPinLeft, int speedPinRight, int dirPinRight,double pid_kp,double pid_ki,double pid_kd);
        ~movement();

        void enable();
        void stop();

        int kp = 0.6;
        int ki = 0.002;
        int kd = 0;
        double setpoint = 0; 
        int baseSpeed = 0; // Base speed for the motors, can be adjusted
        void onExit();
    private:
        bool isEnabled = false;

        MPU6050 gyro;
        Engines eng_L;
        Engines eng_R;
        PID pid;
        void safe();

        void loop();
};