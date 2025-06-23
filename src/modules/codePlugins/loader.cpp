// main.cpp
#include "modules/codePlugins/interface.hpp"
#include "modules/codePlugins/loader.hpp"
#include <dlfcn.h>
#include <dirent.h>
#include <iostream>
#include <vector>

std::vector<LoadedMod> loadMods(const std::string& folder) {
    std::vector<LoadedMod> result;

    DIR* dir = opendir(folder.c_str());
    if (!dir) return result;

    struct dirent* entry;
    while ((entry = readdir(dir))) {
        std::string name = entry->d_name;
        if (name.size() > 3 && name.substr(name.size() - 3) == ".so") {
            std::string path = folder + "/" + name;

            void* handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle) continue;

            CreateModFunc create = (CreateModFunc)dlsym(handle, "createMod");
            if (!create) {
                dlclose(handle);
                continue;
            }

            IMod* mod = create();
            if (!mod) {
                dlclose(handle);
                continue;
            }

            std::cout << "Loaded mod: " << mod->getName() << " v" << mod->getVersion() << "\n";
            mod->onLoad();

            result.push_back({handle, mod});
        }
    }

    closedir(dir);
    return result;
}
