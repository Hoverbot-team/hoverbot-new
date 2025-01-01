#include "sensors/gyro.hpp"
#include <iostream>
#include "uart.hpp"
#include <opencv2/opencv.hpp>
#include "navigation/navVideo.hpp"
#include "movement/engines.hpp"
using namespace std;
//global variables
UART uart(115200);
MPU6050 gyro;

float mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void checkArduinoConnection(){
    string in = uart.read();
    while(in != "rr"){
        in = uart.read();
        cout << "no connection" << endl;
    }
    uart.write("ar");
    cout << "connection established" << endl;
}
int main(){
    // Create a VideoCapture object to capture video from the default camera (index 0)
    Engines eng_L(26,27);
    Engines eng_R(23,22);
    cv::VideoCapture camera_cap(0);
    // Check if the camera opened successfully
    if (!camera_cap.isOpened()) {
        std::cerr << "Error: Could not open the camera!" << std::endl;
        return -1;
    }
    vidGuidance VidGuidance(camera_cap);
    //checkArduinoConnection();
    while(1){
    
    }
    
}