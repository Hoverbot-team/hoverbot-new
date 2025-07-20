#include "sensors/rotation/gyro.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "movement/engines.hpp"
#include "movement/PID.hpp"
#include <thread>
#include "movement/movement.hpp"
#include "modules/codePlugins/loader.hpp"
#include "misc/logs/log.hpp"
#include "sensors/rotation/magnetometer.hpp"
using namespace std;
movement Movement(12,5,13,6,0.6,0.002,0);
float mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void onExit() {
    Movement.stop();
    cout << "Exiting program, stopping engines." << endl;
}

int main(){
    auto mods = loadMods("/home/a/plugins/");
    for (auto& mod : mods) {
        mod.instance->onUpdate(0.016f); // fake delta time
    }
    Movement.enable();
    logs.log("Hoverbot started successfully.");
    HMC5883L magnetometer; // Initialize the magnetometer
    /*
    atexit(onExit);
    thread safety(safe); //activate safety system
    safety.detach();
       // Target angle 
    while(1){

    }
    */
   while (true)
   {
   }
   
}