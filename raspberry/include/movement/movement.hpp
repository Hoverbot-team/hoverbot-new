#include <sensors/gyro.hpp>
#include <movement/engines.hpp>
#include <movement/PID.hpp>
#include <thread>
#include <iostream>
class movement {
    public:
        movement() : eng_L(12, 5), eng_R(13, 6) {
            // Initialize the gyro and engines
        }
        ~movement() {
            eng_L.stop();
            eng_R.stop();
        }
        int kp = 0.6;
        int ki = 0.002;
        int kd = 0;
    private:
        MPU6050 gyro;
        Engines eng_L;
        Engines eng_R;
};