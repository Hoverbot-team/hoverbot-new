#include "movement/movement.hpp"

#define max_PWM 20

using namespace std;

float movement::simpleStability(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
movement::movement(int speedPinLeft, int dirPinLeft, int speedPinRight, int dirPinRight, double pid_kp, double pid_ki, double pid_kd) : eng_L(speedPinLeft, dirPinLeft, max_PWM), eng_R(speedPinRight, dirPinRight, max_PWM), pid(pid_kp, pid_ki, pid_kd)
{
    logs.log("initialising movement");

    // thread inits
    thread movementLoop(&movement::loop, this);
    thread safeLoop(&movement::safe, this);
    movementLoop.detach();
    safeLoop.detach();
}

movement::~movement()
{

    eng_L.stop();
    eng_R.stop();
    delayMicroseconds(100);
}

void movement::loop()
{
    logs.log("Movement loop starting");
    while (true)
    {
        auto start = std::chrono::high_resolution_clock::now();
        double correction = pid.calculate(setpoint, gyro.roll());
        cout << "Correction (PID): " << correction << endl;
        if (isEnabled)
        {
            // Calculate motor speeds based on PID correction
            int motorLeftSpeed = (baseSpeed - correction) * 2;
            int motorRightSpeed = (baseSpeed + correction) * 2;

            // Clamp to valid range (-25 to 25 in your case)
            motorLeftSpeed = std::max(-25, std::min(25, motorLeftSpeed));
            motorRightSpeed = std::max(-25, std::min(25, motorRightSpeed));

            // For PWM (always positive)
            int pwmLeft = abs(motorLeftSpeed);
            int pwmRight = abs(motorRightSpeed);

            cout << "Motor Left Speed: " << motorLeftSpeed << ", PWM: " << pwmLeft << endl;
            cout << "Motor Right Speed: " << motorRightSpeed << ", PWM: " << pwmRight << endl;
            cout << "Gyro Roll: " << int(gyro.roll()) << endl;

            // Direction logic
            // Left engine forward if speed >= 0
            eng_L.engine_write(pwmLeft, motorLeftSpeed >= 0);
            eng_R.engine_write(pwmRight, motorRightSpeed >= 0);
            // Optional debug
            // cout << motorLeftSpeed << endl;
            // cout << motorRightSpeed << endl;
            // delayMicroseconds(100);
        }
        else
        {
            stop();
            break;
        }
        std::this_thread::sleep_until(start + std::chrono::milliseconds(50));
    }
}
void movement::enable()
{
    isEnabled = true;
    logs.log("Movement enabled.");
}
void movement::safe()
{
    while (abs(movement::gyro.read_gyro_X()) < 60 && abs(movement::gyro.read_gyro_Y()) < 60 && abs(movement::gyro.read_gyro_Z()) < 60)
    {
        // std::cout<< "safe loop running"<<std::endl;
    }
    eng_L.stop();
    eng_R.stop();
    delayMicroseconds(100);
    logs.log("automatic shutdown event occured");
    exit(0);
}
void movement::stop()
{
    isEnabled = false;
    eng_L.stop();
    eng_R.stop();
    delayMicroseconds(100);
    logs.log("Engines stopped.");
}