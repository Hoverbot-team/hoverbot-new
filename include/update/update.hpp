#include <thread>
#include <iostream>
#include <fstream>
#include "misc/logs/log.hpp"
#include "misc/exec/exec.hpp"
class Update {
#define updateFolder "SCU/Update/"
public:

    Update();
    void SCUUpdateHandler();
    static bool fileExists(const std::string& filename);
};
