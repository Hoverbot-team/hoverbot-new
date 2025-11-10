#include "update/update.hpp"

Update::Update(){
    std::thread updateSCU(&Update::SCUUpdateHandler, this);
    updateSCU.detach();

}
void Update::SCUUpdateHandler(){
    logs.log("SCU Updater installed");
    while(true){
        if(fileExists(updateFolder "update.hex")){
            if(int a = SCUUpdate() != 0){
                throw(-1);
                logs.log("SCU Update returned code" + a);
            }
            

        }
        else{
            std::cout << "No update file found" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }
}
bool Update::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}
uint8_t Update::SCUUpdate(){
    try{
        std::cout<<exec::command("sudo avrdude -c wiring -P /dev/ttyUSB0 -b 115200 -p atmega2560 -D -U flash:w:update/scu/update.hex:i") << std::endl;
        exec::command("rm update/scu/update.hex");
        return 0;
    }catch(...){
        return -1;
    }

    
}