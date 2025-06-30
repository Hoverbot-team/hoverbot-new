#include <sensors/gyro.hpp>
#include <movement/engines.hpp>
#include <movement/PID.hpp>
#include <thread>
#include <iostream>
class movement {
    public:
        movement(int speedPinLeft, int dirPinLeft, int speedPinRight, int dirPinRight);
        ~movement();

        void stop();

        int kp = 0.6;
        int ki = 0.002;
        int kd = 0;
    private:
        MPU6050 gyro;
        Engines eng_L;
        Engines eng_R;
        void safe();
};