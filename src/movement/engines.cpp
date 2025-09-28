#include "movement/engines.hpp"

using namespace std;
Engines::Engines(int Pin, int Dir_pin, int max_pwm) : pin(Pin), dir(Dir_pin), max_PWM(max_pwm)
{
    if (wiringPiSetupGpio() == -1)
    {
        std::cerr << "Failed to initialize WiringPi" << std::endl;
    }
    pinMode(dir, OUTPUT);
    digitalWrite(dir, LOW); // Set direction to safe default
    if (softPwmCreate(Pin, 0, 255) != 0)
    {
        std::cerr << "Failed to initialize soft PWM on pin " << Pin << std::endl;
    }
    softPwmWrite(pin, 0); // Ensure PWM is 0 at startup
}
Engines::~Engines()
{
    softPwmWrite(pin, 0);
    digitalWrite(pin, LOW);
    digitalWrite(dir, LOW);
}
void Engines::engine_write(int speed, bool Direction)
{
    if (speed > max_PWM)
    {

    }
    else
    {
        if (!Stop)
        {
            speed = std::max(0, std::min(95, speed));

            // Set direction pin before PWM
            if (Direction)
            {
                digitalWrite(dir, LOW);
            }
            else
            {
                digitalWrite(dir, HIGH);
            }

            softPwmWrite(pin, speed);
            // Debug output
            std::cout << "[Engine] PWM: " << speed << ", Dir: " << (Direction ? "LOW" : "HIGH") << std::endl;
        }
        else
        {
            stop();
            cout << "engines stopped" << endl;
        }
    }
}
void Engines::stop()
{
    softPwmWrite(pin, 0);
    digitalWrite(pin, LOW);
    digitalWrite(dir, LOW);
}
