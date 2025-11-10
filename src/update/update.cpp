#include "update/update.hpp"

Update::Update(){
    std::thread updateSCU(&Update::SCUUpdateHandler, this);
    updateSCU.detach();

}
void Update::SCUUpdateHandler(){
    logs.log("SCU Updater installed");
    while(true){
        if(fileExists(updateFolder "update.hex")){
            try{
                SCUUpdate();
                logs.log("SCU Update Succeded");
            }catch(...){
                logs.log("SCU Update returned code");
            }
        }
        else{
            std::cout << "No update file found" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(15));
    }
}
bool Update::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}
uint8_t Update::SCUUpdate(){
    try{
        exec::command("sudo avrdude -c wiring -P /dev/ttyUSB0 -b 115200 -p atmega2560 -D -U flash:w:update/scu/update.hex:i");
        exec::command("rm update/scu/update.hex");
        return 0;
    }catch(...){
        return -1;
    }
}