#include "update/update.hpp"

Update::Update(){
    std::thread updateSCU(&Update::SCUUpdateHandler, this);
    updateSCU.detach();

}
void Update::SCUUpdateHandler(){
    logs.log("SCU Updater installed");
    while(true){
        if(fileExists(updateFolder "update.hex")){


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