#include <iostream>
#include <vector>
#include "modules/codePlugins/interface.hpp"
struct LoadedMod {
    void* handle;
    IMod* instance;
};
std::vector<LoadedMod> loadMods(const std::string& folder);