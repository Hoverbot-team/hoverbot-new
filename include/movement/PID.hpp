#ifndef PID_HPP
#define PID_HPP

#include <chrono>

class PID {
private:
    double Kp, Ki, Kd;       // PID constants
    double previousError;    // Previous error for derivative calculation
    double integral;         // Accumulated integral
    std::chrono::high_resolution_clock::time_point lastTime;

public:
    // Constructor
    PID(double Kp, double Ki, double Kd);

    // Method to calculate PID output
    double calculate(double setpoint, double currentAngle);
};

#endif // PID_HPP