#include <thread>
#include <iostream>
#include <fstream>
#include "misc/logs/log.hpp"
#include "misc/exec/exec.hpp"
class Update {
#define updateFolder "update/scu/"
public:

    Update();
    void SCUUpdateHandler();
    static bool fileExists(const std::string& filename);
    uint8_t SCUUpdate();
};
