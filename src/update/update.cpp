#include "update/update.hpp"

Update::Update(){
    std::thread updateSCU(&Update::SCUUpdate, this);
    updateSCU.detach();

}
void Update::SCUUpdate(){
    std::cout << "SCU Updater installed" << std::endl;
    while(true){

    }
}
