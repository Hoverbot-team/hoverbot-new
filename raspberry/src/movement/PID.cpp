#include "movement/PID.hpp"

// Constructor
PID::PID(double Kp, double Ki, double Kd)
    : Kp(Kp), Ki(Ki), Kd(Kd), previousError(0), integral(0) {
    lastTime = std::chrono::high_resolution_clock::now();
}

// Method to calculate PID output
double PID::calculate(double setpoint, double currentAngle) {
    auto now = std::chrono::high_resolution_clock::now();
    double dt = std::chrono::duration<double>(now - lastTime).count();
    lastTime = now;

    // Calculate error
    double error = setpoint - currentAngle;

    // Calculate integral and derivative
    integral += error * dt;
    double derivative = (error - previousError) / dt;

    // Compute PID output
    double output = Kp * error + Ki * integral + Kd * derivative;

    // Save error for next derivative calculation
    previousError = error;

    return output;
}