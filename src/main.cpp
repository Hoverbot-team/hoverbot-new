#include "sensors/rotation/gyro.hpp"
#include <iostream>
#include <csignal>
#include <opencv2/opencv.hpp>
#include "movement/engines.hpp"
#include "movement/PID.hpp"
#include <thread>
#include "movement/movement.hpp"
#include "modules/codePlugins/loader.hpp"
#include "misc/logs/log.hpp"
#include "update/update.hpp"
using namespace std;
movement Movement(12,5,13,6,0.3,0,0);
void handleSigint(int sig){
    cout << "SIGINT received, stopping movement..." << endl;
    Movement.stop();
    logs.log("Movement stopped due to SIGINT.");
    exit(0);
}
int main(){
    signal(SIGINT, handleSigint);
    signal(SIGTERM, handleSigint);
    Update update;
    logs.log("Hoverbot started successfully.");
   while (true)
   {
   }

}
